/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:09 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:55:29 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

float	mat_determinant(t_mat4 m)
{
	const float	det = m.i.x * (m.j.y * (m.k.z * m.p.w - m.k.w * m.p.z) - m.j.z
			* (m.k.y * m.p.w - m.k.w * m.p.y) + m.j.w
			* (m.k.y * m.p.z - m.k.z * m.p.y)) - m.i.y
		* (m.j.x * (m.k.z * m.p.w - m.k.w * m.p.z) - m.j.z
			* (m.k.x * m.p.w - m.k.w * m.p.x) + m.j.w
			* (m.k.x * m.p.z - m.k.z * m.p.x)) + m.i.z
		* (m.j.x * (m.k.y * m.p.w - m.k.w * m.p.y) - m.j.y
			* (m.k.x * m.p.w - m.k.w * m.p.x) + m.j.w
			* (m.k.x * m.p.y - m.k.y * m.p.x)) - m.i.w
		* (m.j.x * (m.k.y * m.p.z - m.k.z * m.p.y) - m.j.y
			* (m.k.x * m.p.z - m.k.z * m.p.x) + m.j.z
			* (m.k.x * m.p.y - m.k.y * m.p.x));

	return (det);
}

t_mat4	mat_inverse(t_mat4 m)
{
	const float		det = mat_determinant(m);
	const t_mat4	adj = adjugate(m);
	t_mat4			inv;

	if (det < EPSILON)
		return (m);
	inv.i.x = adj.i.x * (1.0f / det);
	inv.i.y = adj.i.y * (1.0f / det);
	inv.i.z = adj.i.z * (1.0f / det);
	inv.i.w = adj.i.w * (1.0f / det);
	inv.j.x = adj.j.x * (1.0f / det);
	inv.j.y = adj.j.y * (1.0f / det);
	inv.j.z = adj.j.z * (1.0f / det);
	inv.j.w = adj.j.w * (1.0f / det);
	inv.k.x = adj.k.x * (1.0f / det);
	inv.k.y = adj.k.y * (1.0f / det);
	inv.k.z = adj.k.z * (1.0f / det);
	inv.k.w = adj.k.w * (1.0f / det);
	inv.p.x = adj.p.x * (1.0f / det);
	inv.p.y = adj.p.y * (1.0f / det);
	inv.p.z = adj.p.z * (1.0f / det);
	inv.p.w = adj.p.w * (1.0f / det);
	return (inv);
}
