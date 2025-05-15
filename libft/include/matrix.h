/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:25:33 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 15:25:44 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <math.h>
# include "vector.h"
# define EPSILON 0.001f
# define MAX_SCALE 1000.0f

typedef struct s_mat4
{
	t_vec4	i;
	t_vec4	j;
	t_vec4	k;
	t_vec4	p;
}	t_mat4;

t_mat4		adjugate(t_mat4 m);
void		mat_scale(t_mat4 *m, float sx, float sy, float sz);
void		mat_transpose_inverse(t_mat4 mat);
void		mat_rotate(t_mat4 *m, float dx, float dy, float dz);
void		mat_translate(t_mat4 *m, float dx, float dy, float dz);
t_vec4		mat_apply(t_mat4 mat, t_vec4 v);
t_mat4		mat_compose(t_mat4 m2, t_mat4 m1);
t_mat4		mat_transpose(t_mat4 m);
t_mat4		mat_init_id(void);
t_mat4		mat_orthogonal(t_vec4 dir);
t_mat4		mat_inverse(t_mat4 matrix);

#endif
