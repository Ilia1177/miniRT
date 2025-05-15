/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_orthogonal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:12 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:55:29 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

// If forward is parallel to up, create a fallback right vector
t_mat4	mat_orthogonal(t_vec4 forward)
{
	t_mat4			orthogonal;
	const t_vec4	up = {0, 1, 0, 0};
	t_vec4			right;
	t_vec4			new_up;

	forward = normalize_vec4(forward);
	right = normalize_vec4(cross_vec4(up, forward));
	if (mag_vec4(right) < EPSILON)
		right = (t_vec4){1, 0, 0, 0};
	new_up = normalize_vec4(cross_vec4(forward, right));
	orthogonal = mat_init_id();
	orthogonal.i = right;
	orthogonal.j = new_up;
	orthogonal.k = forward;
	orthogonal.p = (t_vec4){0, 0, 0, 1};
	return (orthogonal);
}
