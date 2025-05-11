/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:00:48 by npolack           #+#    #+#             */
/*   Updated: 2025/05/11 11:37:21 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rotate_obj(t_mat4 *tm, float dx, float dy, float dz)
{
	t_vec4	s;
	t_mat4	new;
	t_mat4	m;

	m = *tm;
	s.x = mag_vec4(m.i);
	s.y = mag_vec4(m.j);
	s.z = mag_vec4(m.k);
	new.i = normalize_vec4(m.i);
	new.j = normalize_vec4(m.j);
	new.k = normalize_vec4(m.k);
	new.p = (t_vec4){0, 0, 0, 1};
	mat_translate(&new, m.p.x, m.p.y, m.p.z);
	mat_rotate(&new, dx, dy, dz);
	mat_scale(&new, s.x, s.y, s.z);
	*tm = new;
	print_mat4(*tm);
}
/*****************************************************************************
* the variable rend allow to not render all the times
* the rendering is only when you press a key
* +=1 and -=1 allow to press to key and when release one the rendering continue
******************************************************************************/
int	key_press(int keysym, t_data *scene)
{
	if (keysym == XK_Escape)
		rt_shut_down(scene);
	else if (keysym >= 0 && keysym < 99999)
	{
		scene->rend += 1;
		scene->key_state[keysym] = 1;
	}
	return (keysym);
}

int	key_release(int keysym, t_data *scene)
{
	if (scene->rend > 0)
		scene->rend -= 1;
	if (keysym >= 0 && keysym < 99999)
		scene->key_state[keysym] = 0;
	return (keysym);
}

void	show_selected_object(t_data *scene, t_object *last_obj)
{
	static t_argb	last_color;

	if (scene->selected && scene->selected != last_obj)
	{
		if (last_obj)
			last_obj->color = last_color;
		last_color = scene->selected->color;
		scene->selected->color = argb_inverse(scene->selected->color);
		print_mat4(scene->selected->t_m);
		print_mat4(mat_inverse(scene->selected->t_m));
	}
	else if (scene->selected && scene->selected == last_obj)
	{
		print_mat4(scene->selected->t_m);
		print_mat4(mat_inverse(scene->selected->t_m));
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
	t_vec2		cnv;
	//t_viewport	vp;
	t_object	*last_obj;
	t_painter	catcher;

	catcher.lim[0] = EPSILON;
	catcher.lim[1] = T_MAX;
	last_obj = scene->selected;
	//vp = scene->viewport;
	cnv.x = x - (WIDTH / 2);
	cnv.y = (HEIGHT / 2) - y;
	catcher.ray.d = projection(cnv, scene);
	catcher.ray.d = mat_apply(scene->cam.t_m, catcher.ray.d);
	catcher.ray.o = scene->cam.t_m.p;
	catcher.ray.v.w = -1.0f;
	scene->selected = closest_intersect(&catcher, 0, scene->objects);
	show_selected_object(scene, last_obj);
}
