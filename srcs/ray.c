/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:32:49 by npolack           #+#    #+#             */
/*   Updated: 2025/03/13 18:08:58 by npolack          ###   ########.fr       */
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
	pt = add_vec3(mult_vec3(dir, obj->closest_t), scene->cam.pos);
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
	float		closest_t;
	float		*t;

	(void)t_max;
	(void)t_min;
	closest_t = FLT_MAX;
	closest_obj	= NULL;
	while (obj)
	{
		t = obj->t;
		if (intersect_object(origin, dir, obj))
		{
			if (obj->closest_t < closest_t)
			{
				closest_t = obj->closest_t;
				closest_obj = obj;
			}
			/* if (t[0] >= t_min && t[0] <= t_max && t[0] < closest_t) */
			/* { */
			/* 	closest_t = t[0]; */
			/* 	closest_obj = obj; */
			/* } */
			/* if (t[1] >= t_min && t[1] <= t_max && t[1] < closest_t) */
			/* { */
			/* 	closest_t = t[1]; */
			/* 	closest_obj = obj; */
			/* } */
		}
		obj = obj->next;
	}
	if (closest_obj)
		closest_obj->closest_t = closest_t;
	return (closest_obj);
}

int	intersect_object(t_vec3 origin, t_vec3 dir, t_object *obj)
{
	if (obj->type == SPHERE && intersect_sphere(origin, dir, obj))
		return (1);
	else if (obj->type == CYLINDER && intersect_cylinder(origin, dir, obj))
		return (1);
	else if (obj->type == PLANE && intersect_plane(origin, dir, obj))
		return (1);
	return (0);
}

int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *object)
{
	t_quad	quad;
	t_vec3	oc;

	oc = sub_vec3(origin, object->pos);
	quad = solve_quadratic(oc, dir, object->radius);
	object->t[0] = quad.t[0];
	object->t[1] = quad.t[1];
	object->closest_t = FLT_MAX;
	if (quad.delta < 0)
		return (0);
	if (quad.t[0] < 0 && quad.t[1] < 0)
		return (0);
	if (quad.t[0] >= 0 && quad.t[0] < quad.t[1])
		object->closest_t = quad.t[0];
	else if (quad.t[1] >= 0 && quad.t[1] < quad.t[0])
		object->closest_t = quad.t[1];
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
		quad.t[0] = FLT_MAX;
		quad.t[1] = FLT_MAX;
		return (quad);
	}
	square_root = sqrtf(quad.delta);
	quad.t[0] = (-quad.b - square_root) / (2.0f * quad.a);
	quad.t[1] = (-quad.b + square_root) / (2.0f * quad.a);
	return (quad);
}

int	intersect_cylinder(t_vec3 origin, /*t_rtray ray,*/ t_vec3 dir, t_object *cylinder) //, float *t)
{
    t_quad quad;
    t_vec3 oc;
    t_vec3 axis;
	float	mn[2];
	float	y[2];

	oc = sub_vec3(origin, cylinder->pos);
    axis = normalize_vec3(cylinder->orientation);

    // Projection du rayon et origine sur l'axe du cylindre
    mn[0] = dot_vec3(dir, axis);
    mn[1] = dot_vec3(oc, axis);

    // Composantes perpendiculaires
    t_vec3 d_perp = sub_vec3(dir, mult_vec3(axis, mn[0]));
    t_vec3 o_perp = sub_vec3(oc, mult_vec3(axis, mn[1]));
    quad = solve_quadratic(o_perp, d_perp, cylinder->radius);
	cylinder->t[0] = quad.t[0];
	cylinder->t[1] = quad.t[1];
	cylinder->closest_t = FLT_MAX;
    if (quad.delta < 0)
		return (0);
    // Vérification des bornes du cylindre (en hauteur)
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];
	if ((y[0] < 0 || y[0] > cylinder->height) && (y[1] < 0 || y[1] > cylinder->height))
        return (0);
	/* if (quad.t[0] <= 0 && quad.t[1] <= 0) */
	/* 	return (0); */
	/* if (quad.t[0] < quad.t[1]) */
	/* 	cylinder->closest_t = quad.t[0]; */
	/* else if (quad.t[1] < quad.t[0]) */
	/* 	cylinder->closest_t = quad.t[1]; */
    cylinder->closest_t = (y[0] >= 0 && y[0] <= cylinder->height) ? quad.t[0] : quad.t[1];
    return (1);
}

int	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *plane)
{
	t_vec3		diff;
	const float	denom = dot_vec3(plane->orientation, dir);

	//t_vec3	normal = sub_vec3(pt, obj->pos);
	//normal = normalize_vec3(normal);
	// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
	if (fabs(denom) < 1e-6)
		return (0);
	// Calcul de l'intersection
	diff = sub_vec3(plane->pos, origin);
//idiff = (t_vec3){plane.pos.x - ray.origin.x, plane.pos.y - ray.origin.y,
//			plane.pos.z - ray.origin.z};
	plane->closest_t = dot_vec3(diff, plane->orientation) / denom;
	if (plane->closest_t > 1)
		return (1);
	return (0);
}
