#include <miniRT_bonus.h>

void	speak(t_data *scene, char *msg)
{
	pthread_mutex_lock(&scene->speak);
	printf("%s\n", msg);
	pthread_mutex_unlock(&scene->speak);
}

int	all_ready(t_painter *painter)
{
	int	i;

	i = -1;
	while (++i < THREAD_NB)
	{
		pthread_mutex_lock(&painter[i].brush);
		if (painter[i].ready == 0)
		{
			pthread_mutex_unlock(&painter[i].brush);
			return (0);
		}
		pthread_mutex_unlock(&painter[i].brush);
	}
	return (1);
}
int	rt_render(t_data *scene)
{
	int	i;

	while (!all_ready(scene->painter))
		;
	pthread_mutex_lock(&scene->print);
	scene->is_printing = 1;
	pthread_mutex_unlock(&scene->print);

	speak(scene, "listener is working");
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	handle_input(scene);	
	i = -1;
	while (++i < THREAD_NB)
	{
		pthread_mutex_lock(&scene->painter[i].brush);
		scene->painter[i].ready = 0;
		speak(scene, "threads back to work");
		pthread_mutex_unlock(&scene->painter[i].brush);
	}

	speak(scene, "listener attempt to lock print");
	pthread_mutex_lock(&scene->print);
	speak(scene, "not printing anymore");
	scene->is_printing = 0;
	pthread_mutex_unlock(&scene->print);
	//printf("listener is realising\n");
	//i = -1;
	//while (++i < THREAD_NB)
	//	sem_post(scene->print);
	//usleep(500000);
//	printf("rendering\n");
//	pthread_mutex_lock(&scene->mutex);
//	while (scene->is_painting) {
//		pthread_cond_wait(&scene->modifyer, &scene->mutex);
//    }
//    scene->is_printing = 1;  
//	pthread_mutex_unlock(&scene->mutex);
//
//	printf("listener is printing && updating\n");
//	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
//	handle_input(scene);
//
//	pthread_mutex_lock(&scene->mutex);
//    scene->is_printing = 0;  
//	pthread_cond_broadcast(&scene->brush);
//    pthread_mutex_unlock(&scene->mutex);
	return (0);
}

int	display_scene(t_data *scene)
{
	mlx_hook(scene->win, 2, 1L << 0, &key_press, scene);
	mlx_hook(scene->win, 3, 1L << 1, &key_release, scene);
	mlx_hook(scene->win, 17, 1L << 2, &rt_shut_down, scene);
	mlx_hook(scene->win, 4, 1L << 2, &mouse_press, scene);
	mlx_hook(scene->win, 5, 1L << 3, &mouse_release, scene);
	mlx_hook(scene->win, 6, 1L << 6, &mouse_pos, scene);
	mlx_loop_hook(scene->mlx, &rt_render, scene);
	scene->status = th_painter_start(scene);
	if (!scene->status)
		th_listener_start(scene);
	else
		rt_shut_down(scene);
	return (0);
}

int	main(int ac, char **av)
{
	int status;
	t_data	scene;

	status = rt_init(&scene, ac, av);
	if (!status)
		status = build_scene(&scene);
	if (status)
		free_data(&scene);
	else if (ac == 3)
	{
		scene.res = 1;
		display_color(&scene, NULL);
		save_as_ppm(&scene.img, av[2]);
		rt_shut_down(&scene);
	}
	else if (ac == 2)
		display_scene(&scene);
	return (status);
}
