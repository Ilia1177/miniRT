/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:19:47 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 14:47:37 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	handle_light_move(t_data *scene)
{
	t_light	*light;

	light = select_light(&scene->lights);
	if (scene->key_state[XK_KP_Left] == 1)
		light->pos.x -= 0.3;
	if (scene->key_state[XK_KP_Right] == 1)
		light->pos.x += 0.3;
	if (scene->key_state[XK_KP_Up] == 1)
		light->pos.y += 0.3;
	if (scene->key_state[XK_KP_Down] == 1)
		light->pos.y -= 0.3;
	if (scene->key_state[XK_KP_End] == 1)
		light->pos.z -= 0.3;
	if (scene->key_state[XK_KP_Next] == 1)
		light->pos.z += 0.3;
}
