/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:14 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:55:29 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/matrix.h"

void	mat_rotate(t_mat4 *m, float dx, float dy, float dz)
{
	const float	tx = dx * (M_PI / 180.0f);
	const float	ty = dy * (M_PI / 180.0f);
	const float	tz = dz * (M_PI / 180.0f);
	t_mat4		r;

	r.p = (t_vec4){0, 0, 0, 1};
	r.i = normalize_vec4((t_vec4){1, 0, 0, 0});
	r.j = normalize_vec4((t_vec4){0, cos(tx), sin(tx), 0});
	r.k = normalize_vec4((t_vec4){0, -sin(tx), cos(tx), 0});
	*m = mat_compose(*m, r);
	r.i = normalize_vec4((t_vec4){cos(ty), 0, -sin(ty), 0});
	r.j = normalize_vec4((t_vec4){0, 1, 0, 0});
	r.k = normalize_vec4((t_vec4){sin(ty), 0, cos(ty), 0});
	*m = mat_compose(*m, r);
	r.i = normalize_vec4((t_vec4){cos(tz), sin(tz), 0, 0});
	r.j = normalize_vec4((t_vec4){-sin(tz), cos(tz), 0, 0});
	r.k = normalize_vec4((t_vec4){0, 0, 1, 0});
	*m = mat_compose(*m, r);
}

void	mat_scale(t_mat4 *m, float sx, float sy, float sz)
{
	t_vec4	vec;
	float	lim;

	vec.w = 0;
	vec = mult_vec4(m->i, sx);
	lim = mag_vec4(vec);
	if (lim < MAX_SCALE && lim > EPSILON)
		m->i = mult_vec4(m->i, sx);
	vec = mult_vec4(m->j, sy);
	lim = mag_vec4(vec);
	if (lim < MAX_SCALE && lim > EPSILON)
		m->j = mult_vec4(m->j, sy);
	vec = mult_vec4(m->k, sz);
	lim = mag_vec4(vec);
	if (lim < MAX_SCALE && lim > EPSILON)
		m->k = mult_vec4(m->k, sz);
}

void	mat_translate(t_mat4 *m, float dx, float dy, float dz)
{
	m->p.x += dx;
	m->p.y += dy;
	m->p.z += dz;
}
