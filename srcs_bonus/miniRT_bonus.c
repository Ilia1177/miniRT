#include <miniRT_bonus.h>

int	render(t_data *scene)
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
	mlx_hook(scene->win, 4, 1L << 2, &mouse_press, scene);
	mlx_hook(scene->win, 5, 1L << 3, &mouse_release, scene);
	mlx_hook(scene->win, 6, 1L << 6, &mouse_pos, scene);
	mlx_hook(scene->win, 17, 1L << 2, &rt_shut_down, scene);
	mlx_loop_hook(scene->mlx, &render, scene);
	mlx_loop(scene->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	int status;
	t_data	scene;

	ft_bzero(&scene, sizeof(t_data));
	if (ac < 1)
		return (1);
	else if (ac > 1)
		scene.map_name = av[1];
	status = rt_init(&scene);
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
