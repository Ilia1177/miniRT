/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:32:49 by npolack           #+#    #+#             */
/*   Updated: 2025/03/13 10:30:04 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <miniRT.h>

unsigned int	throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	unsigned int	reflected_color;
	unsigned int	local_color;
	float		luminosity;
	t_vec3		pt;
	t_vec3		normal;
	t_vec3		reflected_ray;
	
	obj = closest_intersect(origin, dir, t_min, t_max, scene->objects);
	if (obj == NULL)
		return (0x00000000);
	pt = add_vec3(mult_vec3(dir, obj->delta), scene->cam.pos);
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

t_object	*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	t_object	*curr_obj;
	float		closest_t;
	float		*solution;

	closest_t = FLT_MAX;
	closest_obj	= NULL;
	curr_obj = obj;
	while (curr_obj)
	{
		solution = curr_obj->intersection;
		intersect_sphere(origin, dir, curr_obj);
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
		closest_obj->delta = closest_t;
	return (closest_obj);
}


int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *object)
{
	t_quad	quad;
	t_vec3	oc;

	oc = sub_vec3(origin, object->pos);
	quad = solve_quadratic(oc, dir, object->radius);
	object->delta = quad.delta;
	object->intersection[0] = quad.t0;
	object->intersection[1] = quad.t1;
	if (quad.delta < 0)
		return (0);
	/* float	r = object->radius; */
	/* float	a, b, c; */
	/* float	delta; */
	/* t_vec3	substract; */

	/* substract = sub_vec3(origin, object->pos); */
	/* a = dot_vec3(dir, dir); */
	/* b = 2 * dot_vec3(substract, dir); */
	/* c = dot_vec3(substract, substract) - r * r; */
	/* delta = b * b - 4 * a * c; */
	/* if (delta < 0) */
	/* { */
	/* 	object->intersection[0] = FLT_MAX; */
	/* 	object->intersection[1] = FLT_MAX; */
	/* 	return (0); */
	/* } */
	/* object->intersection[0] = (-b + sqrt(delta)) / (2 * a); */
	/* object->intersection[1] = (-b - sqrt(delta)) / (2 * a); */
	return (1);
}

t_quad	solve_quadratic(t_vec3 oc, t_vec3 dir, float radius)
{
	t_quad	quad;
	float	square_root;

	quad.a = dot_vec3(dir, dir);
	quad.b = 2.0f * dot_vec3(oc, dir);
	quad.c = dot_vec3(oc, oc) - radius * radius;
	quad.delta = quad.b * quad.b - 4.0f * quad.a * quad.c;
	if (quad.delta < 0)
	{
		quad.t0 = FLT_MAX;
		quad.t1 = FLT_MAX;
		return (quad);
	}
	square_root = sqrtf(quad.delta);
	quad.t0 = (-quad.b - square_root) / (2.0f * quad.a);
	quad.t1 = (-quad.b + square_root) / (2.0f * quad.a);
	return (quad);
}
