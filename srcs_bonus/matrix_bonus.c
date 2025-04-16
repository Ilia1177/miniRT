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
	t_vec4	vec;
	float	lim;

	vec.w = 0;
	vec = mult_vec4(m->i, sx);
	lim = mag_vec4(vec);
	if (lim < MAX_SCALE && lim > 0)
		m->i = mult_vec4(m->i, sx);
	vec = mult_vec4(m->j, sy);
	lim = mag_vec4(vec);
	if (lim < MAX_SCALE && lim > 0)
		m->j = mult_vec4(m->j, sy);
	vec = mult_vec4(m->k, sz);
	lim = mag_vec4(vec);
	if (lim < MAX_SCALE && lim > 0)
		m->k = mult_vec4(m->k, sz);
	inverse = mat_inverse(*m);
	printf("Scale matrix:\n");
	print_mat4(*m);
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

t_mat4 mat_rotate(t_mat4 *m, float dx, float dy, float dz) {
    const float tx = dx * (M_PI / 180.0f);
    const float ty = dy * (M_PI / 180.0f);
    const float tz = dz * (M_PI / 180.0f);

    // X-axis rotation matrix (correct)
    t_mat4 rx = {
        .i = {1, 0, 0, 0},
        .j = {0, cosf(tx), sinf(tx), 0},
        .k = {0, -sinf(tx), cosf(tx), 0},
        .p = {0, 0, 0, 1}
    };

    // Y-axis rotation matrix (FIXED SIGN)
    t_mat4 ry = {
        .i = {cosf(ty), 0, sinf(ty), 0},  // <- i.z = +sin(ty)
        .j = {0, 1, 0, 0},
        .k = {-sinf(ty), 0, cosf(ty), 0}, // <- k.x = -sin(ty)
        .p = {0, 0, 0, 1}
    };

    // Z-axis rotation matrix (correct)
    t_mat4 rz = {
        .i = {cosf(tz), sinf(tz), 0, 0},
        .j = {-sinf(tz), cosf(tz), 0, 0},
        .k = {0, 0, 1, 0},
        .p = {0, 0, 0, 1}
    };

    // Apply rotations in local space: M = M * (Rx * Ry * Rz)
    t_mat4 combined_rot = mat_compose(mat_compose(rx, ry), rz);
    *m = mat_compose(*m, combined_rot);
    return *m;
}

t_mat4	mat_rotate2(t_mat4 *m, float dx, float dy, float dz)
{
	const float	tx = dx * (M_PI / 180.0f);
	const float	ty = dy * (M_PI / 180.0f);
	const float	tz = dz * (M_PI / 180.0f);
//	t_mat4		r;
//
    t_mat4 rx = { // X-axis rotation
        .i = {1, 0, 0, 0},
        .j = {0, cosf(tx), sinf(tx), 0},
        .k = {0, -sinf(tx), cosf(tx), 0},
        .p = {0, 0, 0, 1}
    };
    t_mat4 ry = { // Y-axis rotation
        .i = {cosf(ty), 0, -sinf(ty), 0},
        .j = {0, 1, 0, 0},
        .k = {sinf(ty), 0, cosf(ty), 0},
        .p = {0, 0, 0, 1}
    };
    t_mat4 rz = { // Z-axis rotation
        .i = {cosf(tz), sinf(tz), 0, 0},
        .j = {-sinf(tz), cosf(tz), 0, 0},
        .k = {0, 0, 1, 0},
        .p = {0, 0, 0, 1}
    };
	*m = mat_compose(*m, mat_compose(mat_compose(rx, ry), rz));

//	r.p = (t_vec4){0, 0, 0, 1};
//	r.i = normalize_vec4((t_vec4){1, 0, 0, 0});
//	r.j = normalize_vec4((t_vec4){0, cos(tx), sin(tx), 0});
//	r.k = normalize_vec4((t_vec4){0, -sin(tx), cos(tx), 0});
//	*m = mat_compose(*m, r);
//	r.i = normalize_vec4((t_vec4){cos(ty), 0, -sin(ty), 0});
//	r.j = normalize_vec4((t_vec4){0, 1, 0, 0});
//	r.k = normalize_vec4((t_vec4){sin(ty), 0, cos(ty), 0});
//	*m = mat_compose(*m, r);
//	r.i = normalize_vec4((t_vec4){cos(tz), sin(tz), 0, 0});
//	r.j = normalize_vec4((t_vec4){-sin(tz), cos(tz), 0, 0});
//	r.k = normalize_vec4((t_vec4){0, 0, 1, 0});
//	*m = mat_compose(*m, r);
	printf("Transformation matrix:\n");
	print_mat4(*m);
	return (mat_inverse(*m));
}

t_mat4 mat_compose(t_mat4 m1, t_mat4 m2) {
    t_mat4 res;

    // Column 0 (i)
    res.i.x = m1.i.x*m2.i.x + m1.j.x*m2.i.y + m1.k.x*m2.i.z + m1.p.x*m2.i.w;
    res.i.y = m1.i.y*m2.i.x + m1.j.y*m2.i.y + m1.k.y*m2.i.z + m1.p.y*m2.i.w;
    res.i.z = m1.i.z*m2.i.x + m1.j.z*m2.i.y + m1.k.z*m2.i.z + m1.p.z*m2.i.w;
    res.i.w = m1.i.w*m2.i.x + m1.j.w*m2.i.y + m1.k.w*m2.i.z + m1.p.w*m2.i.w;

    // Column 1 (j)
    res.j.x = m1.i.x*m2.j.x + m1.j.x*m2.j.y + m1.k.x*m2.j.z + m1.p.x*m2.j.w;
    res.j.y = m1.i.y*m2.j.x + m1.j.y*m2.j.y + m1.k.y*m2.j.z + m1.p.y*m2.j.w;
    res.j.z = m1.i.z*m2.j.x + m1.j.z*m2.j.y + m1.k.z*m2.j.z + m1.p.z*m2.j.w;
    res.j.w = m1.i.w*m2.j.x + m1.j.w*m2.j.y + m1.k.w*m2.j.z + m1.p.w*m2.j.w;

    // Column 2 (k)
    res.k.x = m1.i.x*m2.k.x + m1.j.x*m2.k.y + m1.k.x*m2.k.z + m1.p.x*m2.k.w;
    res.k.y = m1.i.y*m2.k.x + m1.j.y*m2.k.y + m1.k.y*m2.k.z + m1.p.y*m2.k.w;
    res.k.z = m1.i.z*m2.k.x + m1.j.z*m2.k.y + m1.k.z*m2.k.z + m1.p.z*m2.k.w;
    res.k.w = m1.i.w*m2.k.x + m1.j.w*m2.k.y + m1.k.w*m2.k.z + m1.p.w*m2.k.w;

    // Column 3 (p/translation)
    res.p.x = m1.i.x*m2.p.x + m1.j.x*m2.p.y + m1.k.x*m2.p.z + m1.p.x*m2.p.w;
    res.p.y = m1.i.y*m2.p.x + m1.j.y*m2.p.y + m1.k.y*m2.p.z + m1.p.y*m2.p.w;
    res.p.z = m1.i.z*m2.p.x + m1.j.z*m2.p.y + m1.k.z*m2.p.z + m1.p.z*m2.p.w;
    res.p.w = m1.i.w*m2.p.x + m1.j.w*m2.p.y + m1.k.w*m2.p.z + m1.p.w*m2.p.w;

    return res;
}
t_mat4	mat_compose2(t_mat4 m1, t_mat4 m2)
{
	t_mat4			res;
	const t_mat4	transposed = mat_transpose(m2);

	res.i.x = dot_vec4(m1.i, m2.i);
	res.i.y = dot_vec4(m1.i, m2.j);
	res.i.z = dot_vec4(m1.i, m2.k);
	res.i.w = dot_vec4(m1.i, m2.p);
	res.j.x = dot_vec4(m1.j, m2.i);
	res.j.y = dot_vec4(m1.j, m2.j);
	res.j.z = dot_vec4(m1.j, m2.k);
	res.j.w = dot_vec4(m1.j, m2.p);
	res.k.x = dot_vec4(m1.k, m2.i);
	res.k.y = dot_vec4(m1.k, m2.j);
	res.k.z = dot_vec4(m1.k, m2.k);
	res.k.w = dot_vec4(m1.k, m2.p);
	res.p.x = dot_vec4(m1.p, m2.i);
	res.p.y = dot_vec4(m1.p, m2.j);
	res.p.z = dot_vec4(m1.p, m2.k);
	res.p.w = dot_vec4(m1.p, m2.p);
	
//	res.i.x = dot_vec4(m1.i, transposed.i);
//	res.i.y = dot_vec4(m1.i, transposed.j);
//	res.i.z = dot_vec4(m1.i, transposed.k);
//	res.i.w = dot_vec4(m1.i, transposed.p);
//	res.j.x = dot_vec4(m1.j, transposed.i);
//	res.j.y = dot_vec4(m1.j, transposed.j);
//	res.j.z = dot_vec4(m1.j, transposed.k);
//	res.j.w = dot_vec4(m1.j, transposed.p);
//	res.k.x = dot_vec4(m1.k, transposed.i);
//	res.k.y = dot_vec4(m1.k, transposed.j);
//	res.k.z = dot_vec4(m1.k, transposed.k);
//	res.k.w = dot_vec4(m1.k, transposed.p);
//	res.p.x = dot_vec4(m1.p, transposed.i);
//	res.p.y = dot_vec4(m1.p, transposed.j);
//	res.p.z = dot_vec4(m1.p, transposed.k);
//	res.p.w = dot_vec4(m1.p, transposed.p);
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


//	t_mat4 mat_inverse3(t_mat4 m) {
//		t_mat4 inv;
//		// Compute inverse of the 3x3 rotation/scale part
//		t_mat3 upper = {m.i.xyz, m.j.xyz, m.k.xyz};
//		t_mat3 inv_upper = mat3_transpose(upper); // For pure rotation
//		// Compute translation adjustment
//		t_vec3 T = m.p.xyz;
//		t_vec3 inv_T = mat3_mul_vec3(inv_upper, T);
//		inv_T = vec3_negate(inv_T);
//		// Build inverse matrix
//		inv.i = (t_vec4){inv_upper.i.x, inv_upper.i.y, inv_upper.i.z, 0};
//		inv.j = (t_vec4){inv_upper.j.x, inv_upper.j.y, inv_upper.j.z, 0};
//		inv.k = (t_vec4){inv_upper.k.x, inv_upper.k.y, inv_upper.k.z, 0};
//		inv.p = (t_vec4){inv_T.x, inv_T.y, inv_T.z, 1};
//		return inv;
//	}
//

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
    inv.i.x = m.i.x;  // Column 0 becomes row 0
    inv.i.y = m.j.x;  // Column 1 becomes row 0
    inv.i.z = m.k.x;  // Column 2 becomes row 0
    inv.i.w = 0.0f;

    inv.j.x = m.i.y;  // Column 0 becomes row 1
    inv.j.y = m.j.y;
    inv.j.z = m.k.y;
    inv.j.w = 0.0f;

    inv.k.x = m.i.z;  // Column 0 becomes row 2
    inv.k.y = m.j.z;
    inv.k.z = m.k.z;
    inv.k.w = 0.0f;

    // Compute inverse translation: -(transposed_rotation * translation)
    inv.p.x = -(m.i.x * m.p.x + m.j.x * m.p.y + m.k.x * m.p.z);
    inv.p.y = -(m.i.y * m.p.x + m.j.y * m.p.y + m.k.y * m.p.z);
    inv.p.z = -(m.i.z * m.p.x + m.j.z * m.p.y + m.k.z * m.p.z);
    inv.p.w = 1.0f;

    return inv;
}
