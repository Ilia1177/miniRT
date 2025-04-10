/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:00 by npolack           #+#    #+#             */
/*   Updated: 2025/04/10 14:55:32 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
// 1. dot_vec3(axis, dir) -> ray perpendiculaire au plan, == we dont see the plane
int	intersect_plane(t_ray *ray, t_object *pl, float *t)
{
	const t_vec4	origin = ray->o;
	const t_vec4	dir = ray->d;
	float			inter;

	(void)pl;
	if (fabs(dir.z) < EPSILON)
		return (0);
	inter = -origin.z / dir.z;
	if (inter > EPSILON)
	{
		*t = inter;
		return (1);
	}
	return (0);
}
