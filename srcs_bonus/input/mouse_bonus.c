/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:57 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 15:31:39 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

int	mouse_pos(int x, int y, t_data *scene)
{
	(void)scene;
	(void)x;
	(void)y;
	return (0);
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
