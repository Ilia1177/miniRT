/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:24:12 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/11 11:07:31 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_light	*select_light(t_light **lights)
{
	t_light	*curr_light;

	curr_light = *lights;
	while (curr_light && curr_light->next && curr_light->type != POINT)
		curr_light = curr_light->next;
	return (curr_light);
}

void	handle_light_move(t_data *scene)
{
	static t_light	*light;

	if (!light)
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
	if (light && scene->key_state[XK_F5] == 1)
	{
		if (!light->next)
			light = select_light(&light);
		else
			light = select_light(&scene->lights);
	}
}
