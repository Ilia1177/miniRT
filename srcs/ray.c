/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:32:49 by npolack           #+#    #+#             */
/*   Updated: 2025/03/14 17:01:52 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <miniRT.h>

// Normalize the cylinder's orientation vector
// Vector from the cylinder's base position to the point
// Project pt_to_base onto the cylinder's axis
// Check if the point is on the curved surface or the end caps
// Point is on the curved surface
// Point is on the bottom cap
// Point is on the top cap
t_vec3 cylinder_normal(t_vec3 pt, t_object *cylinder)
{
    t_vec3 normal;
    const t_vec3	axis = normalize_vec3(cylinder->orientation);
    const t_vec3	pt_to_base = sub_vec3(pt, cylinder->pos);
    const float		projection = dot_vec3(pt_to_base, axis);
    const t_vec3	proj_vec = mult_vec3(axis, projection);

    if (projection > 0 && projection < cylinder->height)
        normal = normalize_vec3(sub_vec3(pt_to_base, proj_vec));
    else if (projection <= 0) 
        normal = mult_vec3(axis, -1.0f); // Normal points opposite to the axis
    else
        normal = axis; // Normal points in the direction of the axis
    return (normal);
}

t_argb	throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	t_argb		reflected_color;
	t_argb		local_color;
	t_argb		luminosity;
	t_vec3		pt;
	t_vec3		normal;
	t_vec3		reflected_ray;
	
	local_color = (t_argb) {0, 0, 0, 0};
	obj = closest_intersect(origin, dir, t_min, t_max, scene->objects);
	if (obj == NULL)
		return (local_color);
	pt = add_vec3(mult_vec3(dir, obj->closest_t), scene->cam.pos);
	if (obj->type == CYLINDER)
		normal = cylinder_normal(pt, obj);
	else if (obj->type == SPHERE)
		normal = normalize_vec3(sub_vec3(pt, obj->pos));
	else
		normal = normalize_vec3(obj->orientation);
	luminosity = compute_lighting(pt, normal, mult_vec3(dir, -1), obj->specular, scene);
	local_color = mult_colors(obj->color, luminosity);
	if (rec <= 0 || obj->reflective.a <= 0)
		return (local_color);
	reflected_ray = reflect_ray(mult_vec3(dir, -1), normal);
	reflected_color = throw_ray(pt, reflected_ray, 0.001, FLT_MAX, rec - 1, scene);
	return (add_colors(mult_colors(local_color, ease_color(obj->reflective, 255)), mult_colors(reflected_color, obj->reflective)));
}

t_object	*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;
	float		*t;

	(void)t_max;
	(void)t_min;
	closest_t = FLT_MAX;
	curr_t = FLT_MAX;
	closest_obj	= NULL;
	while (obj)
	{
		t = obj->t;
		if(intersect_object(origin, dir, obj, &curr_t))
		{
			 if (t[0] >= t_min && t[0] <= t_max && t[0] < closest_t) 
			 { 
			 	closest_t = t[0]; 
			 	closest_obj = obj; 
			 } 
			 if (t[1] >= t_min && t[1] <= t_max && t[1] < closest_t) 
			 { 
			 	closest_t = t[1]; 
			 	closest_obj = obj; 
			 }
		}
		obj = obj->next;
	}
	if (closest_obj)
		closest_obj->closest_t = closest_t;
	return (closest_obj);
}

int	intersect_object(t_vec3 origin, t_vec3 dir, t_object *obj, float *t)
{
	if (obj->type == SPHERE && intersect_sphere(origin, dir, obj, t))
		return (1);
	else if (obj->type == CYLINDER && intersect_cylinder(origin, dir, obj, t))
		return (1);
	else if (obj->type == PLANE && intersect_plane(origin, dir, obj))
		return (1);
	return (0);
}

int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec3	oc;

	oc = sub_vec3(origin, sphere->pos);
	quad = solve_quadratic(oc, dir, sphere->radius);
	sphere->t[0] = quad.t[0];
	sphere->t[1] = quad.t[1];
	sphere->closest_t = FLT_MAX;
	if (quad.delta < 0)
		return (0);
	if (quad.t[0] < 0 && quad.t[1] < 0)
		return (0);
	if (quad.t[0] >= 0 && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] >= 0 && quad.t[1] < quad.t[0])
		*t = quad.t[1];
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

// Projection du rayon et origine sur l'axe du cylindre
// Composantes perpendiculaires
// Vérification des bornes du cylindre (en hauteur)
int	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *cylinder, float *t)
{
    t_quad quad;
    t_vec3 oc;
    t_vec3 axis;
	float	mn[2];
	float	y[2];

	//(void)t;
	oc = sub_vec3(origin, cylinder->pos);
    axis = normalize_vec3(cylinder->orientation);

    mn[0] = dot_vec3(dir, axis);
    mn[1] = dot_vec3(oc, axis);
    t_vec3 d_perp = sub_vec3(dir, mult_vec3(axis, mn[0]));
    t_vec3 o_perp = sub_vec3(oc, mult_vec3(axis, mn[1]));
    quad = solve_quadratic(o_perp, d_perp, cylinder->radius);
	cylinder->t[0] = quad.t[0];
	cylinder->t[1] = quad.t[1];
	cylinder->closest_t = FLT_MAX;
    if (quad.delta < 0)
		return (0);
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];
	if ((y[0] < 0 || y[0] > cylinder->height) && (y[1] < 0 || y[1] > cylinder->height))
        return (0);
	/* if (y[0] >= 0 && y[0] <= cylinder->height) { */
        /* *t = quad.t[0]; */
    /* } else { */
        /* *t = quad.t[1]; */
    /* } */
	if (quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > 0)
		*t = quad.t[1];
    return (1);
}

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
int	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *plane)
{
	const t_vec3	diff = sub_vec3(plane->pos, origin);
	const float		denom = dot_vec3(plane->orientation, dir);

	//t_vec3	normal = sub_vec3(pt, obj->pos);
	//normal = normalize_vec3(normal);
	if (fabs(denom) < 1e-6)
		return (0);
	plane->t[0] = dot_vec3(diff, normalize_vec3(plane->orientation)) / denom;
	plane->t[1] = FLT_MAX;
	if (plane->t[0] > 0)
		return (1);
	return (0);
}
