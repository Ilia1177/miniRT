#include <miniRT.h>

t_vec3	mat_translate(t_matrix mat, t_vec3 v)
{
	t_vec3	res;
	
	res.x = v.x + mat.p.x;
	res.y = v.y + mat.p.y;
	res.z = v.z + mat.p.z;
	res.w = v.w;
	return (res);
}

t_matrix	mat_compose(t_matrix m2, t_matrix m1)
{
	t_matrix		res;
	const t_vec3	x = {m2.i.x, m2.j.x, m2.k.x, m2.p.x};
	const t_vec3	y = {m2.i.y, m2.j.y, m2.k.y, m2.p.y};
	const t_vec3	z = {m2.i.z, m2.j.z, m2.k.z, m2.p.z};
	const t_vec3	w = {m2.i.w, m2.j.w, m2.k.w, m2.p.w};

	res.i.x = dot_vec3(m1.i, x);
	res.i.y = dot_vec3(m1.i, y);
	res.i.z = dot_vec3(m1.i, z);
	res.i.w = dot_vec3(m1.i, w);
	res.j.x = dot_vec3(m1.j, x);
	res.j.y = dot_vec3(m1.j, y);
	res.j.z = dot_vec3(m1.j, z);
	res.j.w = dot_vec3(m1.j, w);
	res.k.x = dot_vec3(m1.k, x);
	res.k.y = dot_vec3(m1.k, y);
	res.k.z = dot_vec3(m1.k, z);
	res.k.w = dot_vec3(m1.k, w);
	res.p.x = dot_vec3(m1.p, x);
	res.p.y = dot_vec3(m1.p, y);
	res.p.z = dot_vec3(m1.p, z);
	res.p.w = dot_vec3(m1.p, w);
	return (res);
}

// Make a transform matrix from axis and position of object
t_matrix	mat_generate(t_object *obj)
{
	t_matrix		trans_mat;
	const t_vec3	world_up = (t_vec3) {0, 1, 0, 0};

	trans_mat.k = obj->axis;
	trans_mat.i = normalize_vec3(cross_vec3(trans_mat.k, world_up));
	trans_mat.j = cross_vec3(trans_mat.k, trans_mat.i);
	trans_mat.p = obj->pos;
	return (trans_mat);
}

// Apply the matrix on a vector
t_vec3	mat_apply(t_matrix mat, t_vec3 v)
{
	t_vec3	res;
	const t_vec3 x = {mat.i.x, mat.j.x, mat.k.x, mat.p.x};
	const t_vec3 y = {mat.i.y, mat.j.y, mat.k.y, mat.p.y};
	const t_vec3 z = {mat.i.z, mat.j.z, mat.k.z, mat.p.z};
	const t_vec3 w = {mat.i.w, mat.j.w, mat.k.w, mat.p.w};

	res.x = dot_vec3(v, x);
	res.y = dot_vec3(v, y);
	res.z = dot_vec3(v, z);
	res.w = dot_vec3(v, w);
	return (res);
}

void inverse_matrix(t_matrix matrix, t_matrix *inv_matrix)
{
    // Transpose the rotation part (rows become columns)
    inv_matrix->i = (t_vec3) { matrix.i.x, matrix.j.x, matrix.k.x, 0 };
    inv_matrix->j = (t_vec3) { matrix.i.y, matrix.j.y, matrix.k.y, 0 };
    inv_matrix->k = (t_vec3) { matrix.i.z, matrix.j.z, matrix.k.z, 0 };

    // Compute the inverse translation: -R^T * T
    inv_matrix->p.x = -(inv_matrix->i.x * matrix.p.x + inv_matrix->i.y * matrix.p.y + inv_matrix->i.z * matrix.p.z);
    inv_matrix->p.y = -(inv_matrix->j.x * matrix.p.x + inv_matrix->j.y * matrix.p.y + inv_matrix->j.z * matrix.p.z);
    inv_matrix->p.z = -(inv_matrix->k.x * matrix.p.x + inv_matrix->k.y * matrix.p.y + inv_matrix->k.z * matrix.p.z);
    inv_matrix->p.w = 1;
   	// Homogeneous coordinate remains 1
}
