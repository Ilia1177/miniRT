/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:06:49 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/02 16:20:26 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// translate object on z axis zith i and j
static void	handle_object_translation(t_data *scene)
{
	if (scene->key_state[XK_i] == 1 && scene->selected)
		scene->selected->pos.z += 0.1;
	if (scene->key_state[XK_k] == 1 && scene->selected)
		scene->selected->pos.z -= 0.1;
	if (scene->key_state[XK_l] == 1 && scene->selected)
		scene->selected->pos.x += 0.1;
	if (scene->key_state[XK_j] == 1 && scene->selected)
		scene->selected->pos.x -= 0.1;
	if (scene->key_state[XK_u] == 1 && scene->selected)
		scene->selected->pos.y += 0.1;
	if (scene->key_state[XK_o] == 1 && scene->selected)
		scene->selected->pos.y -= 0.1;
}

static void	handle_object_rotation(t_data *scene)
{
	if (scene->key_state[XK_z] == 1 && scene->selected)
		rotate_on_x(scene->selected, 1.0f);
	if (scene->key_state[XK_x] == 1 && scene->selected)
		rotate_on_y(scene->selected, 1.0f);
	if (scene->key_state[XK_c] == 1 && scene->selected)
		rotate_on_z(scene->selected, 1.0f);
}

// translate object on z axis zith i and j
static void	handle_object_resize(t_data *scene)
{
	if (scene->key_state[XK_v] == 1 && scene->selected)
		scene->selected->radius += 0.1;
	if (scene->key_state[XK_b] == 1 && scene->selected)
		scene->selected->radius -= 0.1;
	if (scene->selected->type == CYLINDER)
	{
		if (scene->key_state[XK_n] == 1 && scene->selected)
			scene->selected->height += 0.1;
		if (scene->key_state[XK_m] == 1 && scene->selected)
			scene->selected->height -= 0.1;
	}
}

static void	handle_camera_move(t_data *scene)
{
	if (scene->key_state[XK_Left] == 1)
		scene->cam.yaw += 5;
	if (scene->key_state[XK_Right] == 1)
		scene->cam.yaw -= 5;
	if (scene->key_state[XK_Down] == 1 && scene->cam.pitch > -85.0f)
		scene->cam.pitch -= 5;
	if (scene->key_state[XK_Up] == 1 && scene->cam.pitch < 85.0f)
		scene->cam.pitch += 5;
	if (scene->key_state[XK_w] == 1)
		move_camera_forward(&scene->cam, 0.5);
	if (scene->key_state[XK_s] == 1)
		move_camera_backward(&scene->cam, 0.5);
	if (scene->key_state[XK_a] == 1)
		move_camera_left(&scene->cam, 0.5);
	if (scene->key_state[XK_d] == 1)
		move_camera_right(&scene->cam, 0.5);
}

int	handle_input(t_data *scene)
{
	if (scene->selected)
	{
		handle_object_translation(scene);
		handle_object_rotation(scene);
		handle_object_resize(scene);
	}
	handle_light_move(scene);
	handle_camera_move(scene);
	if (scene->key_state[XK_F1] == 1 && scene->res < 10)
		scene->res++;
	if (scene->key_state[XK_F2] == 1 && scene->res > 1)
		scene->res--;
	return (0);
}
