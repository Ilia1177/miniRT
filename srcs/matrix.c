/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:24:43 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 16:23:50 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_matrix	mat_compose(t_matrix m2, t_matrix m1)
{
	t_matrix		res;
	const t_vec4	x = {m2.i.x, m2.j.x, m2.k.x, m2.p.x};
	const t_vec4	y = {m2.i.y, m2.j.y, m2.k.y, m2.p.y};
	const t_vec4	z = {m2.i.z, m2.j.z, m2.k.z, m2.p.z};
	const t_vec4	w = {m2.i.w, m2.j.w, m2.k.w, m2.p.w};

	res.i.x = dot_vec4(m1.i, x);
	res.i.y = dot_vec4(m1.i, y);
	res.i.z = dot_vec4(m1.i, z);
	res.i.w = dot_vec4(m1.i, w);
	res.j.x = dot_vec4(m1.j, x);
	res.j.y = dot_vec4(m1.j, y);
	res.j.z = dot_vec4(m1.j, z);
	res.j.w = dot_vec4(m1.j, w);
	res.k.x = dot_vec4(m1.k, x);
	res.k.y = dot_vec4(m1.k, y);
	res.k.z = dot_vec4(m1.k, z);
	res.k.w = dot_vec4(m1.k, w);
	res.p.x = dot_vec4(m1.p, x);
	res.p.y = dot_vec4(m1.p, y);
	res.p.z = dot_vec4(m1.p, z);
	res.p.w = dot_vec4(m1.p, w);
	return (res);
}

// Make a transform matrix from axis and position of object
t_matrix	mat_generate(t_object *obj)
{
	t_matrix		trans_mat;
	const t_vec4	world_up = (t_vec4){0, 1, 0, 0};

	trans_mat.k = obj->axis;
	trans_mat.i = normalize_vec4(cross_vec4(trans_mat.k, world_up));
	trans_mat.j = cross_vec4(trans_mat.k, trans_mat.i);
	trans_mat.p = obj->pos;
	return (trans_mat);
}

// Apply the matrix on a vector
t_vec4	mat_apply(t_matrix mat, t_vec4 v)
{
	t_vec4			res;
	const t_vec4	x = {mat.i.x, mat.j.x, mat.k.x, mat.p.x};
	const t_vec4	y = {mat.i.y, mat.j.y, mat.k.y, mat.p.y};
	const t_vec4	z = {mat.i.z, mat.j.z, mat.k.z, mat.p.z};
	const t_vec4	w = {mat.i.w, mat.j.w, mat.k.w, mat.p.w};

	res.x = dot_vec4(v, x);
	res.y = dot_vec4(v, y);
	res.z = dot_vec4(v, z);
	res.w = dot_vec4(v, w);
	return (res);
}
