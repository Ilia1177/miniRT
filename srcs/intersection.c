/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:01:51 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 11:19:46 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/****************************************************************************
 * check if rau intersect the cylinder
 * first intersect the lateral surface of cylinder 
 * second intersect the top of the cylinder add_vec3
 * third intersect the bottom of the cylinder sub_vev3
 ****************************************************************************/
int	intersect_cylinder(t_ray *ray, t_object *cyl, float *t)
{
	float	t_tmp;
	float	t_min;
	int		hit;
	t_vec4	center;

	t_tmp = INFINITY;
	t_min = INFINITY;
	hit = 0;
	if (intersect_cylinder_lateral(ray, cyl, &t_tmp))
		get_min_t(&t_min, t_tmp, &hit);
	center = add_vec4(cyl->pos, mult_vec4(normalize_vec4(cyl->axis),
				cyl->height / 2));
	if (intersect_disk(ray, center, cyl, &t_tmp) && t_tmp < t_min)
		get_min_t(&t_min, t_tmp, &hit);
	center = sub_vec4(cyl->pos, mult_vec4(normalize_vec4(cyl->axis),
				cyl->height / 2));
	if (intersect_disk(ray, center, cyl, &t_tmp) && t_tmp < t_min)
		get_min_t(&t_min, t_tmp, &hit);
	if (hit)
		*t = t_min;
	return (hit);
}

t_object	*closest_intersect(t_ray *ray, int shadow, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;

	closest_t = t_max;
	curr_t = t_max;
	closest_obj	= NULL;
	while (obj)
	{
		if (intersect_object(ray, obj, &curr_t))
		{
				if (shadow && curr_t >= t_min && curr_t < t_max)
					return (obj);
			if (curr_t < closest_t && curr_t >= t_min && curr_t < t_max)
			{
				closest_t = curr_t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
	{
		closest_obj->t = closest_t;
		if (shadow)
			printf("shadow caught\n");
	}
	return (closest_obj);
}

// ray equation p = o + t * d;
// with :
// p = point
// o = origin of the ray
// t = coeff on direction
// d = direction of the ray
int	intersect_object(t_ray *ray, t_object *obj, float *t)
{
	if (obj->type == SPHERE && intersect_sphere(ray, obj, t))
		return (1);
	else if (obj->type == CYLINDER && intersect_cylinder(ray, obj, t))
		return (1);
	else if (obj->type == PLANE && intersect_plane(ray, obj, t))
		return (1);
	return (0);
}

int	intersect_sphere_exp(t_ray *ray, t_object *sp, float *t)
{
	t_vec4 dir = ray->d;
	t_vec4 o = ray->o;

	float a = dot_vec4(dir, dir);
	float b = 2.0f * dot_vec4(o, dir);
	float c = dot_vec4(o, o) - (sp->radius * sp->radius);

	float delta = b * b - 4 * a * c;

	if (delta < 0) {
		return 0;
	}
	float sqrt_disc = sqrtf(delta);
	float t0 = (-b - sqrt_disc) / (2.0f * a);
	float t1 = (-b + sqrt_disc) / (2.0f * a);

	if (t0 < 0.001f && t1 < 0.0f)
		return (0);
	else if (t0 > 0.001f && t0 < t1)
		*t = t0;
	else if (t1 > 0.00f)
		*t = t1;
	ray->o = add_vec4(mult_vec4(dir, *t), o);
	return (1);
}

// Equation of sphere:
// dist(p, sphere->center) = rayon^2
int	intersect_sphere(t_ray *ray, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec4	oc;

	oc = sub_vec4(ray->o, sphere->pos);
	quad = solve_quadratic(oc, ray->d, sphere->radius);
	if (quad.delta < 0.0f)
		return (0);
	else if (quad.t[0] < 0.001f && quad.t[1] < 0.0f)
		return (0);
	else if (quad.t[0] > 0.001f && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > 0.00f)
		*t = quad.t[1];
	return (1);
}

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
// 1. dot(axis, dir) -> ray perpendiculaire au plan, == we dont see the plane
// 2 
int	intersect_plane(t_ray *ray, t_object *plane, float *t)
{
	const float	denom = dot_vec4(plane->axis, ray->d);
	t_vec4		diff;
	float		inter;

	if (fabs(denom) < 1e-6)
		return (0);
	diff = sub_vec4(plane->pos, ray->o);
	inter = dot_vec4(diff, plane->axis) / denom;
	if (inter > 0)
	{
		*t = inter;
		return (1);
	}
	return (0);
}

int	intersect_cylinder2(t_ray *ray, t_object *cylinder, float *t)
{
	t_vec4 center = cylinder->pos;
    t_quad quad;
    t_vec4 oc, axis, d_perp, o_perp;
    float mn[2], y[2];

    oc = sub_vec4(ray->o, center);
    axis = normalize_vec4(cylinder->axis);

    // Project ray direction and origin onto the cylinder's axis
    mn[0] = dot_vec4(ray->d, axis);
    mn[1] = dot_vec4(oc, axis);
    d_perp = sub_vec4(ray->d, mult_vec4(axis, mn[0]));
    o_perp = sub_vec4(oc, mult_vec4(axis, mn[1]));

    // Solve quadratic equation for intersection points
    quad = solve_quadratic(o_perp, d_perp, cylinder->radius);
    if (quad.delta < 0)
        return (0); // No real intersection

    // Compute y-coordinates of intersection points along the cylinder's axis
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];

    // Check if intersections are within the cylinder's height
    int valid0 = (y[0] >= 0 && y[0] <= cylinder->height);
    int valid1 = (y[1] >= 0 && y[1] <= cylinder->height);

    // Ensure the correct intersection is chosen
    if (!valid0 && !valid1)
        return (0);
    if (valid0 && valid1)
    {
        // If inside the object, pick the second intersection (exit point)
		if (quad.t[0] > 0.001f && quad.t[0] < quad.t[1])
			*t = quad.t[0];
		else if (quad.t[1] > 0)
			*t = quad.t[1];
    }
    else
    {
        // Otherwise, pick the valid intersection
		if (valid0 && quad.t[0] < quad.t[1])
			*t = quad.t[0];
		else if (quad.t[1] > 0)
			*t = quad.t[1];
       // *t = valid0 ? quad.t[0] : quad.t[1];
    }
    // Ensure that the intersection is in the forward direction of the ray
	if (*t < 0)
		return (0); // Intersection is behind the ray's origin
    return (1);
}

int intersect_cylinderoldold(t_ray *ray, t_object *cyl, float *t)
{
    t_vec4 axis = normalize_vec4(cyl->axis);
    t_vec4 base = cy_center_to_base(*cyl); 
    t_vec4 oc = sub_vec4(ray->o, base);
    float mn[2], y[2];
    t_quad quad;

    // Project ray direction and origin onto the cylinder's axis
    mn[0] = dot_vec4(ray->d, axis);       // Projection de la direction du rayon sur l'axe
    mn[1] = dot_vec4(oc, axis);           // Projection de l'origine du rayon sur l'axe
    t_vec4 d_perp = sub_vec4(ray->d, mult_vec4(axis, mn[0]));
    t_vec4 o_perp = sub_vec4(oc, mult_vec4(axis, mn[1]));

    quad = solve_quadratic(o_perp, d_perp, cyl->radius);

    if (quad.delta < 0)
    	return 0;

    // Compute y-coordinates of intersection points along the cylinder's axis
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];

    // Check if intersections are within the cylinder's height
    int valid0 = (y[0] >= 0 && y[0] <= cyl->height);
    int valid1 = (y[1] >= 0 && y[1] <= cyl->height);

    if (!valid0 && !valid1) 
    	return 0; // Intersections hors du cylindre

    // 2. Intersection avec les disques des bases
    float t_cap[2];
    int cap_hit = 0;

    // Base inférieure
    if (fabsf(mn[0]) > EPSILON) 
    {
        t_cap[0] = (-mn[1]) / mn[0]; // Intersection avec le plan z=0
        t_vec4 hit = add_vec4(ray->o, mult_vec4(ray->d, t_cap[0]));
        if (mag_vec4(sub_vec4(hit, base)) <= cyl->radius && t_cap[0] > 0)
            cap_hit = 1;
    }

    // Base supérieure
    if (fabsf(mn[0]) < EPSILON)
    {
        t_cap[1] = (cyl->height - mn[1]) / mn[0]; // Intersection avec le plan z=height
        t_vec4 hit = add_vec4(ray->o, mult_vec4(ray->d, t_cap[1]));
        t_vec4 top = add_vec4(base, mult_vec4(axis, cyl->height));
        if (mag_vec4(sub_vec4(hit, top)) <= cyl->radius && t_cap[1] > 0)
            if (!cap_hit || t_cap[1] < t_cap[0])
            	cap_hit = 2;
    }

    // Combine les intersections (tube + disques)
    float t_min = INFINITY;
    if (valid0 && quad.t[0] > EPSILON && quad.t[0] < t_min)
    	t_min = quad.t[0];
    if (valid1 && quad.t[1] > EPSILON && quad.t[1] < t_min)
    	t_min = quad.t[1];
    if (cap_hit == 1 && t_cap[0] > EPSILON && t_cap[0] < t_min)
    	t_min = t_cap[0];
    if (cap_hit == 2 && t_cap[1] > EPSILON && t_cap[1] < t_min)
    	t_min = t_cap[1];

    if (t_min == INFINITY)
    	return 0;
    *t = t_min;
    return 1;
}
