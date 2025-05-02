/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:28:34 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/02 17:34:53 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	key_press(int keysym, t_data *scene)
{
	if (keysym == XK_Escape)
		rt_shut_down(scene);
	else if (keysym > 0 && keysym < 99999)
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
	if (keysym > 0 && keysym < 99999)
		scene->key_state[keysym] = 0;
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_data *scene)
{
	(void)keycode;
	scene->mouse.x = x;
	scene->mouse.y = y;
	scene->mouse_state = 1;
	select_object(scene);
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
