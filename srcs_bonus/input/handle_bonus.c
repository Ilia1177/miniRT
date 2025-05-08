/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:26:20 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 15:27:59 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_object_scaling(t_data *scene, t_mat4 *tm)
{
	const float	pscale = 1.1f;
	const float	mscale = 0.9f;

	if (scene->key_state[XK_r] == 1)
		mat_scale(tm, pscale, 1.0f, 1.0f);
	if (scene->key_state[XK_t] == 1)
		mat_scale(tm, 1.0f, pscale, 1.0f);
	if (scene->key_state[XK_y] == 1)
		mat_scale(tm, 1.0f, 1.0f, pscale);
	if (scene->key_state[XK_f] == 1)
		mat_scale(tm, mscale, 1.0f, 1.0f);
	if (scene->key_state[XK_g] == 1)
		mat_scale(tm, 1.0f, mscale, 1.0f);
	if (scene->key_state[XK_h] == 1)
		mat_scale(tm, 1.0f, 1.0f, mscale);
}

void	handle_object_translation(t_data *scene, t_mat4 *tm)
{
	if (scene->key_state[XK_i] == 1 && scene->selected)
		mat_translate(tm, 0, 0, 0.1f);
	if (scene->key_state[XK_k] == 1 && scene->selected)
		mat_translate(tm, 0, 0, -0.1f);
	if (scene->key_state[XK_l] == 1 && scene->selected)
		mat_translate(tm, 0.1f, 0, 0);
	if (scene->key_state[XK_j] == 1 && scene->selected)
		mat_translate(tm, -0.1f, 0, 0);
	if (scene->key_state[XK_u] == 1 && scene->selected)
		mat_translate(tm, 0, 0.1f, 0);
	if (scene->key_state[XK_o] == 1 && scene->selected)
		mat_translate(tm, 0, -0.1f, 0);
}

void	handle_object_rotation(t_data *scene, t_mat4 *tm)
{
	const float	speed = 5.0f;

	if (scene->key_state[XK_z] == 1)
		rotate_obj(tm, speed, 0, 0);
	if (scene->key_state[XK_x] == 1)
		rotate_obj(tm, 0, speed, 0);
	if (scene->key_state[XK_c] == 1)
		rotate_obj(tm, 0, 0, speed);
	if (scene->key_state[XK_Z] == 1)
		mat_rotate(tm, -speed, 0, 0);
	if (scene->key_state[XK_X] == 1 && scene->selected)
		mat_rotate(tm, 0, -speed, 0);
	if (scene->key_state[XK_C] == 1 && scene->selected)
		mat_rotate(tm, 0, 0, -speed);
}

void	handle_camera_move(t_data *scene)
{
	const float	speed = 2.0f;

	if (scene->key_state[XK_Left] == 1)
		rotate_camera(&scene->cam, 0, speed, 0);
	if (scene->key_state[XK_Right] == 1)
		rotate_camera(&scene->cam, 0, -speed, 0);
	if (scene->key_state[XK_Down] == 1)
		rotate_camera(&scene->cam, -speed, 0, 0);
	if (scene->key_state[XK_Up] == 1)
		rotate_camera(&scene->cam, speed, 0, 0);
	if (scene->key_state[XK_e] == 1)
		translate_camera(&scene->cam, 0.0f, -speed, 0.0f);
	if (scene->key_state[XK_q] == 1)
		translate_camera(&scene->cam, 0.0f, 0.5, 0.0f);
	if (scene->key_state[XK_w] == 1)
		translate_camera(&scene->cam, 0.0f, 0.0f, 0.5f);
	if (scene->key_state[XK_s] == 1)
		translate_camera(&scene->cam, 0.0f, 0.0f, -0.5f);
	if (scene->key_state[XK_a] == 1)
		translate_camera(&scene->cam, -0.5f, 0.0f, 0.0f);
	if (scene->key_state[XK_d] == 1)
		translate_camera(&scene->cam, 0.5f, 0, 0);
}

int	handle_input(t_data *scene)
{
	t_mat4	*tm;

	if (scene->selected)
	{
		tm = &scene->selected->t_m;
		handle_object_translation(scene, tm);
		handle_object_rotation(scene, tm);
		handle_object_scaling(scene, tm);
	}
	handle_camera_move(scene);
	if (scene->key_state[XK_space] == 1)
		save_as_ppm(&scene->img, "img.ppm");
	if (scene->key_state[XK_F1] == 1 && scene->res < 10)
		scene->res++;
	if (scene->key_state[XK_F2] == 1 && scene->res > 1)
		scene->res--;
	return (0);
}
