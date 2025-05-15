/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_adjugate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:54:17 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:54:22 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

static	t_vec4	cofactor_column1(t_mat4 m)
{
	t_vec4	cofactor;

	cofactor.x = m.j.y * (m.k.z * m.p.w - m.k.w * m.p.z)
		- m.j.z * (m.k.y * m.p.w - m.k.w * m.p.y)
		+ m.j.w * (m.k.y * m.p.z - m.k.z * m.p.y);
	cofactor.y = -m.i.y * (m.k.z * m.p.w - m.k.w * m.p.z)
		+ m.i.z * (m.k.y * m.p.w - m.k.w * m.p.y)
		- m.i.w * (m.k.y * m.p.z - m.k.z * m.p.y);
	cofactor.z = m.i.y * (m.j.z * m.p.w - m.j.w * m.p.z)
		- m.i.z * (m.j.y * m.p.w - m.j.w * m.p.y)
		+ m.i.w * (m.j.y * m.p.z - m.j.z * m.p.y);
	cofactor.w = -m.i.y * (m.j.z * m.k.w - m.j.w * m.k.z)
		+ m.i.z * (m.j.y * m.k.w - m.j.w * m.k.y)
		- m.i.w * (m.j.y * m.k.z - m.j.z * m.k.y);
	return (cofactor);
}

static	t_vec4	cofactor_column2(t_mat4 m)
{
	t_vec4	cofactor;

	cofactor.x = -m.j.x * (m.k.z * m.p.w - m.k.w * m.p.z)
		+ m.j.z * (m.k.x * m.p.w - m.k.w * m.p.x)
		- m.j.w * (m.k.x * m.p.z - m.k.z * m.p.x);
	cofactor.y = m.i.x * (m.k.z * m.p.w - m.k.w * m.p.z)
		- m.i.z * (m.k.x * m.p.w - m.k.w * m.p.x)
		+ m.i.w * (m.k.x * m.p.z - m.k.z * m.p.x);
	cofactor.z = -m.i.x * (m.j.z * m.p.w - m.j.w * m.p.z)
		+ m.i.z * (m.j.x * m.p.w - m.j.w * m.p.x)
		- m.i.w * (m.j.x * m.p.z - m.j.z * m.p.x);
	cofactor.w = m.i.x * (m.j.z * m.k.w - m.j.w * m.k.z)
		- m.i.z * (m.j.x * m.k.w - m.j.w * m.k.x)
		+ m.i.w * (m.j.x * m.k.z - m.j.z * m.k.x);
	return (cofactor);
}

static	t_vec4	cofactor_column3(t_mat4 m)
{
	t_vec4	cofactor;

	cofactor.x = m.j.x * (m.k.y * m.p.w - m.k.w * m.p.y)
		- m.j.y * (m.k.x * m.p.w - m.k.w * m.p.x)
		+ m.j.w * (m.k.x * m.p.y - m.k.y * m.p.x);
	cofactor.y = -m.i.x * (m.k.y * m.p.w - m.k.w * m.p.y)
		+ m.i.y * (m.k.x * m.p.w - m.k.w * m.p.x)
		- m.i.w * (m.k.x * m.p.y - m.k.y * m.p.x);
	cofactor.z = m.i.x * (m.j.y * m.p.w - m.j.w * m.p.y)
		- m.i.y * (m.j.x * m.p.w - m.j.w * m.p.x)
		+ m.i.w * (m.j.x * m.p.y - m.j.y * m.p.x);
	cofactor.w = -m.i.x * (m.j.y * m.k.w - m.j.w * m.k.y)
		+ m.i.y * (m.j.x * m.k.w - m.j.w * m.k.x)
		- m.i.w * (m.j.x * m.k.y - m.j.y * m.k.x);
	return (cofactor);
}

static	t_vec4	cofactor_column4(t_mat4 m)
{
	t_vec4	cofactor;

	cofactor.x = -m.j.x * (m.k.y * m.p.z - m.k.z * m.p.y)
		+ m.j.y * (m.k.x * m.p.z - m.k.z * m.p.x)
		- m.j.z * (m.k.x * m.p.y - m.k.y * m.p.x);
	cofactor.y = m.i.x * (m.k.y * m.p.z - m.k.z * m.p.y)
		- m.i.y * (m.k.x * m.p.z - m.k.z * m.p.x)
		+ m.i.z * (m.k.x * m.p.y - m.k.y * m.p.x);
	cofactor.z = -m.i.x * (m.j.y * m.p.z - m.j.z * m.p.y)
		+ m.i.y * (m.j.x * m.p.z - m.j.z * m.p.x)
		- m.i.z * (m.j.x * m.p.y - m.j.y * m.p.x);
	cofactor.w = m.i.x * (m.j.y * m.k.z - m.j.z * m.k.y)
		- m.i.y * (m.j.x * m.k.z - m.j.z * m.k.x)
		+ m.i.z * (m.j.x * m.k.y - m.j.y * m.k.x);
	return (cofactor);
}

// Compute each cofactor for the adjugate matrix (transposed cofactor matrix)
t_mat4	adjugate(t_mat4 m)
{
	t_mat4	adj;

	adj.i = cofactor_column1(m);
	adj.j = cofactor_column2(m);
	adj.k = cofactor_column3(m);
	adj.p = cofactor_column4(m);
	return (adj);
}
