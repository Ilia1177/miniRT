/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/26 17:59:08 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	clean_scene(t_data *scene)
{
	scene->res = 5;
	scene->cam.pos = (t_vec3){0, 0, -20, 0};
	scene->cam.dir = (t_vec3){0, 0, 1, 0};
	scene->cam.up = (t_vec3){0, 1, 0, 0};
	scene->cam.right = (t_vec3){1, 0, 0, 0};
	scene->cam.yaw = 90.0f;
	scene->cam.pitch = 0.0f;
	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.h = 1;
	scene->viewport.w = calc_vp_width(53, 2);
	scene->objects = NULL;
	scene->lights = NULL;
	return (0);
}

int	scene_init(t_data *scene)
{
	//t_light	*it;

	clean_scene(scene);
//	if (clean_lights(scene) == -109)
//	{
//		print_error_msg(-109);
//		return (-109);
//	}
	//printf("**************************linked list LIGHT**************\n");
	//it = scene->lights;
	//while (it)
	//{
	//	print_light(*it);
	//	it = it->next;
	//}
	return (0);
}
