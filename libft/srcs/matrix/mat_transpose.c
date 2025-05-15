/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_transpose.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:16 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:55:30 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

t_mat4	mat_transpose(t_mat4 m)
{
	t_mat4	transposed;

	transposed.i = (t_vec4){m.i.x, m.j.x, m.k.x, m.p.x};
	transposed.j = (t_vec4){m.i.y, m.j.y, m.k.y, m.p.y};
	transposed.k = (t_vec4){m.i.z, m.j.z, m.k.z, m.p.z};
	transposed.p = (t_vec4){m.i.w, m.j.w, m.k.w, m.p.w};
	return (transposed);
}
