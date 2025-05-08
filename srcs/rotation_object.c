/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:34:58 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/02 16:25:56 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	change_axis(t_object *obj)
{
	t_vec4	new_axis;

	new_axis.x = obj->right.x * obj->axis.x + obj->up.x
		* obj->axis.y + obj->dir.x * obj->axis.z;
	new_axis.y = obj->right.y * obj->axis.x + obj->up.y
		* obj->axis.y + obj->dir.y * obj->axis.z;
	new_axis.z = obj->right.z * obj->axis.x + obj->up.z
		* obj->axis.y + obj->dir.z * obj->axis.z;
	obj->axis = normalize_vec4(new_axis);
}

void	rotate_on_x(t_object *obj, float theta)
{
	t_mat4	mat;

	theta = theta * (M_PI / 180.0f);
	mat.j = (t_vec4){0, cos(theta), sin(theta), 0};
	mat.k = (t_vec4){0, -sin(theta), cos(theta), 0};
	mat.i = normalize_vec4(cross_vec4(obj->up, obj->dir));
	mat.p = (t_vec4){0, 0, 0, 1};
	obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
}

void	rotate_on_y(t_object *obj, float theta)
{
	t_mat4	mat;

	theta = theta * (M_PI / 180.0f);
	mat.i = (t_vec4){cos(theta), 0, -sin(theta), 0};
	mat.k = (t_vec4){sin(theta), 0, cos(theta), 0};
	mat.j = cross_vec4(mat.k, mat.i);
	mat.p = (t_vec4){0, 0, 0, 1};
	obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
}

void	rotate_on_z(t_object *obj, float theta)
{
	t_mat4	mat;

	theta = theta * (M_PI / 180.0f);
	mat.i = (t_vec4){cos(theta), sin(theta), 0, 0};
	mat.j = (t_vec4){-sin(theta), cos(theta), 0, 0};
	mat.k = cross_vec4(mat.i, mat.j);
	mat.p = (t_vec4){0, 0, 0, 1};
	obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
}
