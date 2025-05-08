/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:53:44 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:54:11 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>
//t_object	*closest_intersect(t_ray *ray, int shw, float *lim, t_object *obj)
t_object	*closest_intersect(t_painter *painter, int shadow, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;
	const float	*lim = painter->lim;

	closest_t = INFINITY;
	curr_t = INFINITY;
	closest_obj = NULL;
	while (obj)
	{
		if (intersect_object(&painter->ray, obj, &curr_t))
		{
			if (curr_t >= lim[0] && curr_t < lim[1] && shadow)
				return (obj);
			if (curr_t >= lim[0] && curr_t < lim[1] && curr_t < closest_t)
			{
				closest_t = curr_t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		painter->t = closest_t;
	return (closest_obj);
}

int	intersect_object(t_ray *ray, t_object *obj, float *t)
{
	t_ray			local_ray;
	int				intersect;
	const t_mat4	inv = mat_inverse(obj->t_m);

	intersect = 0;
	local_ray.d = mat_apply(inv, ray->d);
	local_ray.o = mat_apply(inv, ray->o);
	if (obj->type == SPHERE && intersect_sphere(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == CYLINDER && intersect_cylinder(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == PLANE && intersect_plane(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == HYPERBOL && intersect_hyperboloid(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == TRIANGLE && intersect_triangle(&local_ray, obj, t))
		intersect = 1;
	return (intersect);
}

int	solve_quadratic(t_quad *quad)
{
	float	square_root;

	quad->delta = quad->b * quad->b - 4.0f * quad->a * quad->c;
	if (quad->delta < 0.0f)
	{
		quad->t[0] = FLT_MAX;
		quad->t[1] = FLT_MAX;
		return (0);
	}
	square_root = sqrtf(quad->delta);
	quad->t[0] = (-quad->b - square_root) / (2.0f * quad->a);
	quad->t[1] = (-quad->b + square_root) / (2.0f * quad->a);
	return (1);
}
