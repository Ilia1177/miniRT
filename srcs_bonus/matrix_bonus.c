/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:10:37 by npolack           #+#    #+#             */
/*   Updated: 2025/04/11 12:34:44 by npolack          ###   ########.fr       */
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

t_mat4	mat_scale(t_mat4 *m, float sx, float sy, float sz)
{
	t_mat4	inverse;

	m->i = mult_vec4(m->i, sx);
	m->j = mult_vec4(m->j, sy);
	m->k = mult_vec4(m->k, sz);
	inverse = mat_inverse(*m);
	return (inverse);
}

t_mat4	mat_translate(t_mat4 *m, float dx, float dy, float dz)
{
	t_mat4	inverse;

	m->p.x += dx;
	m->p.y += dy;
	m->p.z += dz;
	inverse = mat_inverse(*m);
	return (inverse);
}

t_mat4	mat_rotate(t_mat4 *m, float dx, float dy, float dz)
{
	const float	tx = dx * (M_PI / 180.0f);
	const float	ty = dy * (M_PI / 180.0f);
	const float	tz = dz * (M_PI / 180.0f);
	t_mat4		r;

	r.p = (t_vec4){0, 0, 0, 1};
	r.j = normalize_vec4((t_vec4){0, cos(tx), sin(tx), 0});
	r.k = normalize_vec4((t_vec4){0, -sin(tx), cos(tx), 0});
	r.i = normalize_vec4((t_vec4){1, 0, 0, 0});
	*m = mat_compose(*m, r);
	//rotate by inverse ?? to DELETE TRANSLATION !!
	r.i = normalize_vec4((t_vec4){cos(ty), 0, -sin(ty), 0});
	r.k = normalize_vec4((t_vec4){sin(ty), 0, cos(ty), 0});
	r.j = normalize_vec4((t_vec4){0, 1, 0, 0});
	*m = mat_compose(*m, r);
	r.i = normalize_vec4((t_vec4){cos(tz), sin(tz), 0, 0});
	r.j = normalize_vec4((t_vec4){-sin(tz), cos(tz), 0, 0});
	r.k = normalize_vec4((t_vec4){0, 0, 1, 0});
	*m = mat_compose(*m, r);
	print_mat4(*m);
	return (mat_inverse(*m));
}

t_mat4	mat_compose(t_mat4 m1, t_mat4 m2)
{
	t_mat4			res;
	const t_mat4	transposed = mat_transpose(m2);

	res.i.x = dot_vec4(m1.i, transposed.i);
	res.i.y = dot_vec4(m1.i, transposed.j);
	res.i.z = dot_vec4(m1.i, transposed.k);
	res.i.w = dot_vec4(m1.i, transposed.p);
	res.j.x = dot_vec4(m1.j, transposed.i);
	res.j.y = dot_vec4(m1.j, transposed.j);
	res.j.z = dot_vec4(m1.j, transposed.k);
	res.j.w = dot_vec4(m1.j, transposed.p);
	res.k.x = dot_vec4(m1.k, transposed.i);
	res.k.y = dot_vec4(m1.k, transposed.j);
	res.k.z = dot_vec4(m1.k, transposed.k);
	res.k.w = dot_vec4(m1.k, transposed.p);
	res.p.x = dot_vec4(m1.p, transposed.i);
	res.p.y = dot_vec4(m1.p, transposed.j);
	res.p.z = dot_vec4(m1.p, transposed.k);
	res.p.w = dot_vec4(m1.p, transposed.p);
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

static t_mat4 adjugate(t_mat4 m)
{
    t_mat4 adj;

    // Compute each cofactor for the adjugate matrix (transposed cofactor matrix)
    // Row i (cofactors for original column 1)
    adj.i.x =  m.j.y*(m.k.z*m.p.w - m.k.w*m.p.z) - m.j.z*(m.k.y*m.p.w - m.k.w*m.p.y) + m.j.w*(m.k.y*m.p.z - m.k.z*m.p.y);
    adj.i.y = -m.i.y*(m.k.z*m.p.w - m.k.w*m.p.z) + m.i.z*(m.k.y*m.p.w - m.k.w*m.p.y) - m.i.w*(m.k.y*m.p.z - m.k.z*m.p.y);
    adj.i.z =  m.i.y*(m.j.z*m.p.w - m.j.w*m.p.z) - m.i.z*(m.j.y*m.p.w - m.j.w*m.p.y) + m.i.w*(m.j.y*m.p.z - m.j.z*m.p.y);
    adj.i.w = -m.i.y*(m.j.z*m.k.w - m.j.w*m.k.z) + m.i.z*(m.j.y*m.k.w - m.j.w*m.k.y) - m.i.w*(m.j.y*m.k.z - m.j.z*m.k.y);

    // Row j (cofactors for original column 2)
    adj.j.x = -m.j.x*(m.k.z*m.p.w - m.k.w*m.p.z) + m.j.z*(m.k.x*m.p.w - m.k.w*m.p.x) - m.j.w*(m.k.x*m.p.z - m.k.z*m.p.x);
    adj.j.y =  m.i.x*(m.k.z*m.p.w - m.k.w*m.p.z) - m.i.z*(m.k.x*m.p.w - m.k.w*m.p.x) + m.i.w*(m.k.x*m.p.z - m.k.z*m.p.x);
    adj.j.z = -m.i.x*(m.j.z*m.p.w - m.j.w*m.p.z) + m.i.z*(m.j.x*m.p.w - m.j.w*m.p.x) - m.i.w*(m.j.x*m.p.z - m.j.z*m.p.x);
    adj.j.w =  m.i.x*(m.j.z*m.k.w - m.j.w*m.k.z) - m.i.z*(m.j.x*m.k.w - m.j.w*m.k.x) + m.i.w*(m.j.x*m.k.z - m.j.z*m.k.x);

    // Row k (cofactors for original column 3)
    adj.k.x =  m.j.x*(m.k.y*m.p.w - m.k.w*m.p.y) - m.j.y*(m.k.x*m.p.w - m.k.w*m.p.x) + m.j.w*(m.k.x*m.p.y - m.k.y*m.p.x);
    adj.k.y = -m.i.x*(m.k.y*m.p.w - m.k.w*m.p.y) + m.i.y*(m.k.x*m.p.w - m.k.w*m.p.x) - m.i.w*(m.k.x*m.p.y - m.k.y*m.p.x);
    adj.k.z =  m.i.x*(m.j.y*m.p.w - m.j.w*m.p.y) - m.i.y*(m.j.x*m.p.w - m.j.w*m.p.x) + m.i.w*(m.j.x*m.p.y - m.j.y*m.p.x);
    adj.k.w = -m.i.x*(m.j.y*m.k.w - m.j.w*m.k.y) + m.i.y*(m.j.x*m.k.w - m.j.w*m.k.x) - m.i.w*(m.j.x*m.k.y - m.j.y*m.k.x);

    // Row p (cofactors for original column 4)
    adj.p.x = -m.j.x*(m.k.y*m.p.z - m.k.z*m.p.y) + m.j.y*(m.k.x*m.p.z - m.k.z*m.p.x) - m.j.z*(m.k.x*m.p.y - m.k.y*m.p.x);
    adj.p.y =  m.i.x*(m.k.y*m.p.z - m.k.z*m.p.y) - m.i.y*(m.k.x*m.p.z - m.k.z*m.p.x) + m.i.z*(m.k.x*m.p.y - m.k.y*m.p.x);
    adj.p.z = -m.i.x*(m.j.y*m.p.z - m.j.z*m.p.y) + m.i.y*(m.j.x*m.p.z - m.j.z*m.p.x) - m.i.z*(m.j.x*m.p.y - m.j.y*m.p.x);
    adj.p.w =  m.i.x*(m.j.y*m.k.z - m.j.z*m.k.y) - m.i.y*(m.j.x*m.k.z - m.j.z*m.k.x) + m.i.z*(m.j.x*m.k.y - m.j.y*m.k.x);

    return adj;
}

t_mat4 mat_inverse(t_mat4 m)
{
    const float det = mat_determinant(m);
    if (det < EPSILON)
	{
        ft_printf("Matrix is not invertible\n");
        return (m);
    }
    t_mat4 adj = adjugate(m);
    float inv_det = 1.0f / det;
    t_mat4 inv;
    inv.i.x = adj.i.x * inv_det;
    inv.i.y = adj.i.y * inv_det;
    inv.i.z = adj.i.z * inv_det;
    inv.i.w = adj.i.w * inv_det;
    inv.j.x = adj.j.x * inv_det;
    inv.j.y = adj.j.y * inv_det;
    inv.j.z = adj.j.z * inv_det;
    inv.j.w = adj.j.w * inv_det;
    inv.k.x = adj.k.x * inv_det;
    inv.k.y = adj.k.y * inv_det;
    inv.k.z = adj.k.z * inv_det;
    inv.k.w = adj.k.w * inv_det;
    inv.p.x = adj.p.x * inv_det;
    inv.p.y = adj.p.y * inv_det;
    inv.p.z = adj.p.z * inv_det;
    inv.p.w = adj.p.w * inv_det;
    return inv;
}
t_mat4 mat_inverse2(t_mat4 m)
{
    t_mat4 inv;
    
	inv = mat_transpose(m);
    // Transpose rotation (inverse of orthogonal matrix)
//    inv.i.x = m.i.x;  // Column 0 becomes row 0
//    inv.i.y = m.j.x;  // Column 1 becomes row 0
//    inv.i.z = m.k.x;  // Column 2 becomes row 0
//    inv.i.w = 0.0f;
//
//    inv.j.x = m.i.y;  // Column 0 becomes row 1
//    inv.j.y = m.j.y;
//    inv.j.z = m.k.y;
//    inv.j.w = 0.0f;
//
//    inv.k.x = m.i.z;  // Column 0 becomes row 2
//    inv.k.y = m.j.z;
//    inv.k.z = m.k.z;
//    inv.k.w = 0.0f;

    // Compute inverse translation: -(transposed_rotation * translation)
    inv.p.x = -(m.i.x * m.p.x + m.j.x * m.p.y + m.k.x * m.p.z);
    inv.p.y = -(m.i.y * m.p.x + m.j.y * m.p.y + m.k.y * m.p.z);
    inv.p.z = -(m.i.z * m.p.x + m.j.z * m.p.y + m.k.z * m.p.z);
    inv.p.w = 1.0f;

    return inv;
}
