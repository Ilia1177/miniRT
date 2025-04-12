#include <miniRT_bonus.h>

int	rt_render(t_data *scene)
{

	printf("render\n");
	//scene = painter->sceneref;
	handle_input(scene);
	//display_color(scene, painter);
	
	pthread_mutex_lock(&scene->brush);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	pthread_mutex_unlock(&scene->brush);
	//mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	//atomic_set(scene->brush, 1);
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
		mlx_loop(scene->mlx);
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
