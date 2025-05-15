/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_apply.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:54:30 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:54:32 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

t_vec4	mat_apply(t_mat4 mat, t_vec4 v)
{
	const t_mat4	transposed = mat_transpose(mat);
	t_vec4			res;

	res.x = dot_vec4(v, transposed.i);
	res.y = dot_vec4(v, transposed.j);
	res.z = dot_vec4(v, transposed.k);
	res.w = dot_vec4(v, transposed.p);
	return (res);
}
