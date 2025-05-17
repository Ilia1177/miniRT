/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:42:07 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 10:42:09 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	free_light(t_light *light)
{
	t_light	*old_light;

	while (light)
	{
		old_light = light;
		light = light->next;
		free(old_light);
	}
}

static void	free_objects(t_object **obj)
{
	t_object	*temp_obj;

	if (!obj)
		return ;
	while (*obj)
	{
		temp_obj = (*obj)->next;
		free(*obj);
		*obj = temp_obj;
	}
}

static void	free_data(t_data *scene)
{
	if (scene)
	{
		free_light(scene->lights);
		free_objects(&scene->objects);
	}
}

int	rt_shut_down(t_data *scene)
{
	printf("RT SHUT DOWN\n");
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->img.ptr)
		mlx_destroy_image(scene->mlx, scene->img.ptr);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	free_data(scene);
	exit(0);
}
