/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:14:36 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 17:35:21 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// Calculate triangle edges
// Begin Möller-Trumbore algorithm
// If determinant is near zero, ray is parallel to triangle
// Check u bounds
// Check v bounds and u+v <= 1
// Calculate t value
// Validate t value
int	intersect_triangle(t_ray *ray, t_object *tr, float *t)
{
	const t_vec4	edge1 = sub_vec4(tr->vertice[1], tr->vertice[0]);
	const t_vec4	edge2 = sub_vec4(tr->vertice[2], tr->vertice[0]);
	const float		det = dot_vec4(edge1, cross_vec4(ray->d, edge2));
	t_uv			uv;
	t_vec4			s;

	if (fabsf(det) < EPSILON)
		return (0);
	s = sub_vec4(ray->o, tr->vertice[0]);
	uv.u = (1.0f / det) * dot_vec4(s, cross_vec4(ray->d, edge2));
	if (uv.u < 0.0f || uv.u > 1.0f)
		return (0);
	uv.v = (1.0f / det) * dot_vec4(ray->d, cross_vec4(s, edge1));
	if (uv.v < 0.0f || (uv.u + uv.v) > 1.0f)
		return (0);
	if (((1.0f / det) * dot_vec4(edge2, cross_vec4(s, edge1))) < 0.001f)
		return (0);
	*t = (1.0f / det) * dot_vec4(edge2, cross_vec4(s, edge1));
	return (1);
}
