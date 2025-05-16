/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:08:37 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 11:08:48 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_light(t_light *light)
{
	t_light	*old_light;

	while (light)
	{
		old_light = light;
		light = light->next;
		free(old_light);
	}
}

void	remove_obj(t_object *obj, t_data *scene)
{
	if (!obj)
		return ;
	if (obj->img)
	{
		mlx_destroy_image(scene->mlx, obj->img->ptr);
		free(obj->img);
		free(obj->path);
	}
	free(obj);
}

void	free_objects(t_data *scene)
{
	t_object	*curr_obj;
	t_object	*old_obj;

	if (!scene || !scene->objects)
		return ;
	curr_obj = scene->objects;
	while (curr_obj)
	{
		old_obj = curr_obj;
		curr_obj = curr_obj->next;
		remove_obj(old_obj, scene);
	}
}

void	free_data(t_data *scene)
{
	if (scene)
	{
		free_light(scene->lights);
		free_objects(scene);
	}
}

int	rt_shut_down(t_data *scene)
{
	printf("Shutdown now\n");
	free_data(scene);
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->img.ptr)
		mlx_destroy_image(scene->mlx, scene->img.ptr);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit(scene->status);
	return (scene->status);
}
