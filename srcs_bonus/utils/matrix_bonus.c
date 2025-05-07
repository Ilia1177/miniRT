/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:10:37 by npolack           #+#    #+#             */
/*   Updated: 2025/05/07 12:57:22 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

t_mat4	mat_init_id(void)
{
	t_mat4	id;

	id.i = (t_vec4){1, 0, 0, 0};
	id.j = (t_vec4){0, 1, 0, 0};
	id.k = (t_vec4){0, 0, 1, 0};
	id.p = (t_vec4){0, 0, 0, 1};
	return (id);
}

t_mat4	mat_orthogonal(t_vec4 dir)
{
	t_mat4			orthogonal;
	const t_vec4	up = {0, 1, 0, 0};
	t_vec4			normalized_dir;
	float			mag;
	float			dir_dot_up;

	orthogonal = mat_init_id();
	mag = mag_vec4(dir);
	if (mag < EPSILON)
		return (orthogonal);
	normalized_dir = normalize_vec4(dir);
	orthogonal.k = normalized_dir;
	dir_dot_up = dot_vec3(normalized_dir, up);
	if (fabsf(dir_dot_up) >= 1.0f - EPSILON)
		orthogonal.i = cross_vec4((t_vec4){1, 0, 0, 0}, normalized_dir);
	else
		orthogonal.i = cross_vec4(up, normalized_dir);
	orthogonal.i = normalize_vec4(orthogonal.i);
	orthogonal.j = cross_vec4(orthogonal.k, orthogonal.i);
	orthogonal.p = (t_vec4){0, 0, 0, 1};
	return (orthogonal);
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
	printf("Transformation matrix:\n");
	print_mat4(*m);
}

t_mat4	mat_compose(t_mat4 m1, t_mat4 m2)
{
	t_mat4	res;

	res.i.x = m1.i.x*m2.i.x + m1.j.x*m2.i.y + m1.k.x*m2.i.z + m1.p.x*m2.i.w;
	res.i.y = m1.i.y*m2.i.x + m1.j.y*m2.i.y + m1.k.y*m2.i.z + m1.p.y*m2.i.w;
	res.i.z = m1.i.z*m2.i.x + m1.j.z*m2.i.y + m1.k.z*m2.i.z + m1.p.z*m2.i.w;
	res.i.w = m1.i.w*m2.i.x + m1.j.w*m2.i.y + m1.k.w*m2.i.z + m1.p.w*m2.i.w;
	res.j.x = m1.i.x*m2.j.x + m1.j.x*m2.j.y + m1.k.x*m2.j.z + m1.p.x*m2.j.w;
	res.j.y = m1.i.y*m2.j.x + m1.j.y*m2.j.y + m1.k.y*m2.j.z + m1.p.y*m2.j.w;
	res.j.z = m1.i.z*m2.j.x + m1.j.z*m2.j.y + m1.k.z*m2.j.z + m1.p.z*m2.j.w;
	res.j.w = m1.i.w*m2.j.x + m1.j.w*m2.j.y + m1.k.w*m2.j.z + m1.p.w*m2.j.w;
	res.k.x = m1.i.x*m2.k.x + m1.j.x*m2.k.y + m1.k.x*m2.k.z + m1.p.x*m2.k.w;
	res.k.y = m1.i.y*m2.k.x + m1.j.y*m2.k.y + m1.k.y*m2.k.z + m1.p.y*m2.k.w;
	res.k.z = m1.i.z*m2.k.x + m1.j.z*m2.k.y + m1.k.z*m2.k.z + m1.p.z*m2.k.w;
	res.k.w = m1.i.w*m2.k.x + m1.j.w*m2.k.y + m1.k.w*m2.k.z + m1.p.w*m2.k.w;
	res.p.x = m1.i.x*m2.p.x + m1.j.x*m2.p.y + m1.k.x*m2.p.z + m1.p.x*m2.p.w;
	res.p.y = m1.i.y*m2.p.x + m1.j.y*m2.p.y + m1.k.y*m2.p.z + m1.p.y*m2.p.w;
	res.p.z = m1.i.z*m2.p.x + m1.j.z*m2.p.y + m1.k.z*m2.p.z + m1.p.z*m2.p.w;
	res.p.w = m1.i.w*m2.p.x + m1.j.w*m2.p.y + m1.k.w*m2.p.z + m1.p.w*m2.p.w;
	return (res);
}

t_mat4	mat_transpose(t_mat4 m)
{
	t_mat4	transposed;

	transposed.i = (t_vec4){m.i.x, m.j.x, m.k.x, m.p.x};
	transposed.j = (t_vec4){m.i.y, m.j.y, m.k.y, m.p.y};
	transposed.k = (t_vec4){m.i.z, m.j.z, m.k.z, m.p.z};
	transposed.p = (t_vec4){m.i.w, m.j.w, m.k.w, m.p.w};
	return (transposed);
}

// Apply the matrix on a vector
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

static float mat_determinant(t_mat4 m)
{
	const float	det =
		m.i.x * (m.j.y * (m.k.z * m.p.w - m.k.w * m.p.z) - m.j.z
		* (m.k.y * m.p.w - m.k.w * m.p.y) + m.j.w * (m.k.y * m.p.z - m.k.z * m.p.y))
		- m.i.y * (m.j.x * (m.k.z * m.p.w - m.k.w * m.p.z) - m.j.z
		* (m.k.x * m.p.w - m.k.w * m.p.x) + m.j.w * (m.k.x * m.p.z - m.k.z * m.p.x))
		+ m.i.z * (m.j.x * (m.k.y * m.p.w - m.k.w * m.p.y) - m.j.y
		* (m.k.x * m.p.w - m.k.w * m.p.x) + m.j.w * (m.k.x * m.p.y - m.k.y * m.p.x))
		- m.i.w * (m.j.x * (m.k.y * m.p.z - m.k.z * m.p.y) - m.j.y
		* (m.k.x * m.p.z - m.k.z * m.p.x) + m.j.z * (m.k.x * m.p.y - m.k.y * m.p.x));
    return (det);
}

static t_vec4	cofactor_column1(t_mat4 m)
{
	t_vec4	cofactor;

    cofactor.x =  m.j.y*(m.k.z*m.p.w - m.k.w*m.p.z)
		- m.j.z*(m.k.y*m.p.w - m.k.w*m.p.y) + m.j.w*(m.k.y*m.p.z - m.k.z*m.p.y);
    cofactor.y = -m.i.y*(m.k.z*m.p.w - m.k.w*m.p.z)
		+ m.i.z*(m.k.y*m.p.w - m.k.w*m.p.y) - m.i.w*(m.k.y*m.p.z - m.k.z*m.p.y);
    cofactor.z =  m.i.y*(m.j.z*m.p.w - m.j.w*m.p.z)
		- m.i.z*(m.j.y*m.p.w - m.j.w*m.p.y) + m.i.w*(m.j.y*m.p.z - m.j.z*m.p.y);
    cofactor.w = -m.i.y*(m.j.z*m.k.w - m.j.w*m.k.z)
		+ m.i.z*(m.j.y*m.k.w - m.j.w*m.k.y) - m.i.w*(m.j.y*m.k.z - m.j.z*m.k.y);
	return (cofactor);
}
static t_vec4	cofactor_column2(t_mat4 m)
{
	t_vec4	cofactor;

    cofactor.x = -m.j.x*(m.k.z*m.p.w - m.k.w*m.p.z)
		+ m.j.z*(m.k.x*m.p.w - m.k.w*m.p.x) - m.j.w*(m.k.x*m.p.z - m.k.z*m.p.x);
    cofactor.y =  m.i.x*(m.k.z*m.p.w - m.k.w*m.p.z)
		- m.i.z*(m.k.x*m.p.w - m.k.w*m.p.x) + m.i.w*(m.k.x*m.p.z - m.k.z*m.p.x);
    cofactor.z = -m.i.x*(m.j.z*m.p.w - m.j.w*m.p.z)
		+ m.i.z*(m.j.x*m.p.w - m.j.w*m.p.x) - m.i.w*(m.j.x*m.p.z - m.j.z*m.p.x);
    cofactor.w =  m.i.x*(m.j.z*m.k.w - m.j.w*m.k.z)
		- m.i.z*(m.j.x*m.k.w - m.j.w*m.k.x) + m.i.w*(m.j.x*m.k.z - m.j.z*m.k.x);
	return (cofactor);
}
static t_vec4	cofactor_column3(t_mat4 m)
{
	t_vec4	cofactor;

    cofactor.x =  m.j.x*(m.k.y*m.p.w - m.k.w*m.p.y)
		- m.j.y*(m.k.x*m.p.w - m.k.w*m.p.x) + m.j.w*(m.k.x*m.p.y - m.k.y*m.p.x);
    cofactor.y = -m.i.x*(m.k.y*m.p.w - m.k.w*m.p.y)
		+ m.i.y*(m.k.x*m.p.w - m.k.w*m.p.x) - m.i.w*(m.k.x*m.p.y - m.k.y*m.p.x);
    cofactor.z =  m.i.x*(m.j.y*m.p.w - m.j.w*m.p.y)
		- m.i.y*(m.j.x*m.p.w - m.j.w*m.p.x) + m.i.w*(m.j.x*m.p.y - m.j.y*m.p.x);
    cofactor.w = -m.i.x*(m.j.y*m.k.w - m.j.w*m.k.y)
		+ m.i.y*(m.j.x*m.k.w - m.j.w*m.k.x) - m.i.w*(m.j.x*m.k.y - m.j.y*m.k.x);
	return (cofactor);
}
static t_vec4	cofactor_column4(t_mat4 m)
{
	t_vec4	cofactor;

    cofactor.x = -m.j.x*(m.k.y*m.p.z - m.k.z*m.p.y)
		+ m.j.y*(m.k.x*m.p.z - m.k.z*m.p.x) - m.j.z*(m.k.x*m.p.y - m.k.y*m.p.x);
    cofactor.y =  m.i.x*(m.k.y*m.p.z - m.k.z*m.p.y)
		- m.i.y*(m.k.x*m.p.z - m.k.z*m.p.x) + m.i.z*(m.k.x*m.p.y - m.k.y*m.p.x);
    cofactor.z = -m.i.x*(m.j.y*m.p.z - m.j.z*m.p.y)
		+ m.i.y*(m.j.x*m.p.z - m.j.z*m.p.x) - m.i.z*(m.j.x*m.p.y - m.j.y*m.p.x);
    cofactor.w =  m.i.x*(m.j.y*m.k.z - m.j.z*m.k.y)
		- m.i.y*(m.j.x*m.k.z - m.j.z*m.k.x) + m.i.z*(m.j.x*m.k.y - m.j.y*m.k.x);
	return (cofactor);
}

// Compute each cofactor for the adjugate matrix (transposed cofactor matrix)
static t_mat4 adjugate(t_mat4 m)
{
    t_mat4 adj;

	adj.i = cofactor_column1(m);
	adj.j = cofactor_column2(m);
	adj.k = cofactor_column3(m);
	adj.p = cofactor_column4(m);
    return adj;
}

t_mat4 mat_inverse(t_mat4 m)
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
    return inv;
}
