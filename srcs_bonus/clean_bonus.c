#include <miniRT_bonus.h>

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

void	free_objects(t_object **obj)
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

void	free_data(t_data *scene)
{
	free_light(scene->lights);
	free_objects(&scene->objects);
}


int	rt_shut_down(t_data *scene)
{
	printf("Shutdown with status: %d.\n", scene->status);
	if (THREAD_NB > 1)
	{
		pthread_mutex_lock(&scene->print);
		th_painter_kill(scene);
		scene->processing = 0;
		pthread_cond_broadcast(&scene->painter_rest);
		pthread_mutex_unlock(&scene->print);
		th_painter_wait(scene);
	}
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
	if (THREAD_NB > 1)
		pthread_exit(NULL);
	else
		exit(scene->status);
	return (scene->status);
}
