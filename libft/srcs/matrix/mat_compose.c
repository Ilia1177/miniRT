/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_compose.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:54:37 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:54:39 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

t_mat4	mat_compose(t_mat4 m1, t_mat4 m2)
{
	t_mat4			res;

	res.i = mat_apply(m1, m2.i);
	res.j = mat_apply(m1, m2.j);
	res.k = mat_apply(m1, m2.k);
	res.p = mat_apply(m1, m2.p);
	return (res);
}
