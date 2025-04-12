#include <miniRT_bonus.h>

void *draw_start(void *scene)
{
	return NULL;
}
void	rt_thread_quit(t_data *scene)
{
	return ;
}

int	rt_thread_start(t_data *scn)
{
	pthread_t	master;
	pthread_t	slave[4];
	t_data		*scene;

	scene = scn;
	if (pthread_create(&master, NULL, draw_start, scn))
	{
		rt_thread_quit(scene);
		return (1);
	}
	pthread_join(master, NULL);
	return (0);
}


int	rt_render(t_data *scene)
{
	handle_input(scene);
	display_color(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
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
	//rt_thread_start(scene);
	mlx_loop(scene->mlx);
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
		display_color(&scene);
		save_as_ppm(&scene.img, av[2]);
		rt_shut_down(&scene);
	}
	else if (ac == 2)
		display_scene(&scene);
	return (status);
}
