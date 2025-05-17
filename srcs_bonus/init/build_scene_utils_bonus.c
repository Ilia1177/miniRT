/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_scene_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:17:35 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 15:17:37 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	go_to_endl(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\n' && str[c])
		c++;
	return (c);
}

void	print_all(t_data *scene)
{
	t_object	*obj;
	t_light		*light;

	printf("************************* linked-list OBJECT ***********\n");
	obj = scene->objects;
	while (obj)
	{
		print_obj(*obj);
		obj = obj->next;
	}
	printf("************************* linked-list LIGHT ************\n");
	light = scene->lights;
	while (light)
	{
		print_light(*light);
		light = light->next;
	}
	printf("************************** CAMERA **********************\n");
	print_cam(scene->cam);
}
