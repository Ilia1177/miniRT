/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:00:48 by npolack           #+#    #+#             */
/*   Updated: 2025/04/11 17:52:24 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

void	handle_object_scaling(t_data *scene, t_mat4 *tm, t_mat4 *im)
{
	const float	pscale = 1.1f;
	const float	mscale = 0.9f;

	if (scene->key_state[XK_r] == 1)
		*im = mat_scale(tm, pscale, 1.0f, 1.0f);
	if (scene->key_state[XK_t] == 1)
		*im = mat_scale(tm, 1.0f, pscale, 1.0f);
	if (scene->key_state[XK_y] == 1)
		*im = mat_scale(tm, 1.0f, 1.0f, pscale);
	if (scene->key_state[XK_f] == 1)
		*im = mat_scale(tm, mscale, 1.0f, 1.0f);
	if (scene->key_state[XK_g] == 1)
		*im = mat_scale(tm, 1.0f, mscale, 1.0f);
	if (scene->key_state[XK_h] == 1)
		*im = mat_scale(tm, 1.0f, 1.0f, mscale);
}

void	handle_object_translation(t_data *scene, t_mat4 *tm, t_mat4 *im)
{
	if (scene->key_state[XK_i] == 1 && scene->selected)
		*im = mat_translate(tm, 0, 0, 0.1f);
	if (scene->key_state[XK_k] == 1 && scene->selected)
		*im = mat_translate(tm, 0, 0, -0.1f);
	if (scene->key_state[XK_l] == 1 && scene->selected)
		*im = mat_translate(tm, 0.1f, 0, 0);
	if (scene->key_state[XK_j] == 1 && scene->selected)
		*im = mat_translate(tm, -0.1f, 0, 0);
	if (scene->key_state[XK_u] == 1 && scene->selected)
		*im = mat_translate(tm, 0, 0.1f, 0);
	if (scene->key_state[XK_o] == 1 && scene->selected)
		*im = mat_translate(tm, 0, -0.1f, 0);
}

void	handle_object_rotation(t_data *scene, t_mat4 *tm, t_mat4 *im)
{
	if (scene->key_state[XK_z] == 1)
		*im = mat_rotate(tm, 1.0f, 0, 0);
	if (scene->key_state[XK_x] == 1 && scene->selected)
		*im = mat_rotate(tm, 0, 1.0f, 0);
	if (scene->key_state[XK_c] == 1 && scene->selected)
		*im = mat_rotate(tm, 0, 0, 1.0f);
}

void	handle_camera_move(t_data *scene)
{
	const float speed = 2.0f;

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
	t_mat4	*im;

	if (scene->selected)
	{
		tm = &scene->selected->t_m;
		im = &scene->selected->i_m;
		handle_object_translation(scene, tm, im);
		handle_object_rotation(scene, tm, im);
		handle_object_scaling(scene, tm, im);
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

int	key_press(int keysym, t_data *scene)
{
	if (keysym == XK_Escape)
		rt_shut_down(scene);
	else if (keysym >= 0 && keysym < 99999)
		scene->key_state[keysym] = 1;
	return (keysym);
}

int	key_release(int keysym, t_data *scene)
{
	if (keysym >= 0 && keysym < 99999)
		scene->key_state[keysym] = 0;
	return (keysym);
}

int	mouse_pos(int x, int y, t_data *scene)
{
	static int last_x = 0;
    static int last_y = 0;
    //float delta_x = x - last_x;
    //float delta_y = y - last_y;
	(void)scene;
 //   mouse_move(&scene->cam, delta_x, delta_y);
    last_x = x;
    last_y = y;
//	scene->mouse.x = x;
//	scene->mouse.y = y;
	return (0);
}

void	show_selected_object(t_data *scene, t_object *last_obj)
{
	static t_argb last_color;

	if (scene->selected && scene->selected != last_obj)
	{
		if (last_obj)
			last_obj->color = last_color;
		last_color = scene->selected->color;
		scene->selected->color = invert_color(scene->selected->color);
		printf("selection transform matrix:\n");
		print_mat4(scene->selected->t_m);
	}
	else if (scene->selected && scene->selected == last_obj)
	{
		scene->selected->color = last_color;
		scene->selected = NULL;
		last_obj = NULL;
	}
	else if (!scene->selected && last_obj)
	{
		last_obj->color = last_color;
		last_obj = NULL;
	}
}

void	select_object(t_data *scene, int x, int y)
{
	t_ray		catch_ray;
	t_canvas	cnv;
	t_viewport  vp;
	t_object	*last_obj;
	float		t_lim[2];

	t_lim[0] = EPSILON;
	t_lim[1] = T_MAX;
	last_obj = scene->selected;
	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = x - (cnv.w / 2);
	cnv.loc.y = (cnv.h / 2) - y;
	catch_ray.d = throught_vp(cnv, vp);
	catch_ray.d = mat_apply(scene->cam.t_m, catch_ray.d);
	catch_ray.o = scene->cam.t_m.p;
	catch_ray.v.w = -1.0f;
	scene->selected = closest_intersect(&catch_ray, 0, t_lim, scene->objects);
	show_selected_object(scene, last_obj);
}

int	mouse_press(int keycode, int x, int y, t_data *scene)
{
	(void)keycode;
	select_object(scene, x, y);
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_data *scene)
{
	(void)x;
	(void)y;
	(void)keycode;
	scene->mouse_state = 0;
	return (0);
}
