/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:01:51 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/29 18:29:22 by jhervoch         ###   ########.fr       */
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
				cyl->height / 2.0f));
	if (intersect_disk(ray, center, cyl, &t_tmp))
		get_min_t(&t_min, t_tmp, &hit);
	center = sub_vec4(cyl->pos, mult_vec4(normalize_vec4(cyl->axis),
				cyl->height / 2));
	if (intersect_disk(ray, center, cyl, &t_tmp))
		get_min_t(&t_min, t_tmp, &hit);
	if (hit)
		*t = t_min;
	return (hit);
}

t_object	*closest_intersect(t_painter *painter, int shadow, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		c_t;

	closest_t = painter->tmax;
	c_t = painter->tmax;
	closest_obj = NULL;
	while (obj)
	{
		if (intersect_object(&painter->ray, obj, &c_t))
		{
			if (shadow && c_t >= painter->tmin && c_t < painter->tmax)
				return (obj);
			if (c_t < closest_t && c_t >= painter->tmin && c_t < painter->tmax)
			{
				closest_t = c_t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		closest_obj->t = closest_t;
	return (closest_obj);
}

// Equation of sphere:
// dist(p, sphere->center) = rayon^2
int	intersect_sphere(t_ray *ray, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec4	oc;

	oc = sub_vec4(ray->o, sphere->pos);
	ft_bzero(&quad, sizeof(t_quad));
	quad.a = dot_vec4(ray->d, ray->d);
	quad.b = 2.0f * dot_vec4(oc, ray->d);
	quad.c = dot_vec4(oc, oc) - sphere->radius * sphere->radius;
	if (!solve_gen_quad(&quad))
		return (0);
	else if (quad.t[0] < EPSILON && quad.t[1] < EPSILON)
		return (0);
	else if (quad.t[0] > EPSILON && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > EPSILON)
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

	if (fabs(denom) < EPSILON)
		return (0);
	diff = sub_vec4(plane->pos, ray->o);
	inter = dot_vec4(diff, plane->axis) / denom;
	if (inter > EPSILON)
	{
		*t = inter;
		return (1);
	}
	return (0);
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
