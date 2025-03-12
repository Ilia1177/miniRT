/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:32:49 by npolack           #+#    #+#             */
/*   Updated: 2025/03/12 22:24:38 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <miniRT.h>
#include <math.h>

// get screen's pixel from canvas's point,
t_vec2 cnv_to_screen(t_canvas cnv)
{
	t_vec2 screen;

	screen.x = (cnv.w / 2) + cnv.loc.x;
	screen.y = (cnv.h / 2) - cnv.loc.y;
	return (screen);
}

void	print_vec3(t_vec3 v, char *msg)
{
	printf("%s{x: %f, y: %f, z:%f}\n", msg, v.x, v.y, v.z );
}
// throw ray for every point of the canvas
void	display_color(t_data *scene)
{
	unsigned int	color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;

	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = -cnv.w / 2;
	//mouse_move(&scene->cam, 0.0f, -0.0f);
	while (cnv.loc.x < cnv.w / 2)
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < cnv.h / 2)
		{
			vp.loc = get_viewport_loc(cnv, vp);
			color = throw_ray(scene->cam.pos, vp.loc, 1, FLT_MAX, 8, scene);
			if (color != 0)
				printf("display_color: %X, pix.x: %d, pix.y: %d\n", color, (int)pix.x, (int)pix.y);
			pix = cnv_to_screen(cnv);
			rt_put_pixel(&scene->img, pix, color);
			cnv.loc.y++;
		}
		cnv.loc.x++;
	}
}

// get location of the point in the viemport from canvas'location
t_vec3 get_viewport_loc(t_canvas cnv, t_viewport vp)
{
	t_vec3 vp_loc;

	vp_loc.x = cnv.loc.x * vp.w / cnv.w;
	vp_loc.y = cnv.loc.y * vp.h / cnv.h;
	vp_loc.z = 1;
	return (vp_loc);
}

//	float	closest_intersection(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_data *scene)
//	{
//
//	}

t_object	*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_data *scene)
{
	t_object	*closest_obj;
	t_object	*curr_obj;
	float		closest_t;
	float		*solution;

	closest_t = FLT_MAX;
	closest_obj	= NULL;
	curr_obj = scene->objects;
	while (curr_obj)
	{
		solution = curr_obj->intersection;
		intersect_sphere(origin, dir, curr_obj, scene);
		if (solution[0] >= t_min && solution[0] <= t_max)
		{
			if (solution[0] < closest_t)
			{
				closest_t = solution[0];
				closest_obj = curr_obj;
			}
		}
		if (solution[1] >= t_min && solution[1] <= t_max)
		{
			if (solution[1] < closest_t)
			{
				closest_t = solution[1];
				closest_obj = curr_obj;
			}
		}
		curr_obj = curr_obj->next;
	}
	if (closest_obj)
		closest_obj->discriminant = closest_t;
	return (closest_obj);
}

unsigned int	throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	unsigned int	reflected_color;
	unsigned int	local_color;
	float		luminosity;
	t_vec3		pt;
	t_vec3		normal;
	t_vec3		reflected_ray;


	obj = closest_intersect(origin, dir, t_min, t_max, scene);
	if (obj == NULL)
		return (0x00000000);
	pt = add_vec3(mult_vec3(dir, obj->discriminant), scene->cam.pos);
	normal = sub_vec3(pt, obj->pos);
	normal = normalize_vec3(normal);
	luminosity = compute_lighting(pt, normal, mult_vec3(dir, -1), obj->specular, scene);
	local_color = mult_colors(obj->color, luminosity);
	if (rec <= 0 || obj->reflective <= 0)
		return (local_color);
	reflected_ray = reflect_ray(mult_vec3(dir, -1), normal);
	reflected_color = throw_ray(pt, reflected_ray, 0.001, FLT_MAX, rec - 1, scene);
	return (add_colors(mult_colors(local_color, 1 - obj->reflective), mult_colors(reflected_color, obj->reflective)));
}

int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *object)
{
	float	r = object->radius;
	float	a, b, c;
	float	discriminant;
	t_vec3	substract;

	substract = sub_vec3(origin, object->pos);
	a = dot_vec3(dir, dir);
	b = 2 * dot_vec3(substract, dir);
	c = dot_vec3(substract, substract) - r * r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		object->intersection[0] = FLT_MAX;
		object->intersection[1] = FLT_MAX;
		return (0);
	}
	object->intersection[0] = (-b + sqrt(discriminant)) / (2 * a);
	object->intersection[1] = (-b - sqrt(discriminant)) / (2 * a);
	return (1);
}

t_quad	solve_quadratic(t_vec3 oc, t_vec3 dir, float radius)
{
	t_quad	quad;

	quad.a = vector_dot(dir, dir);
	quad.b = 2.0 * vector_dot(oc, dir);
	quad.c = vector_dot(oc, oc) - radius * radius;
	quad.delta = quad.b * quad.b - 4 * quad.a * quad.c;
	quad.t0 = (-quad.b - sqrtf(quad.delta)) / (2.0 * quad.a);
	quad.t1 = (-quad.b + sqrtf(quad.delta)) / (2.0 * quad.a);
	return (quad);
}
