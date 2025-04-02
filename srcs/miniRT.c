#include <miniRT.h>

int	render(t_data *scene)
{
	if (scene->rend)
	{
		handle_input(scene);
		display_color(scene);
		mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	}
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

	t_matrix	t_m;	
	t_matrix	i_m;	
	float theta = 80 * (M_PI / 180.0f);
	
	t_m.i = (t_vec3) {1, 0, 0, 0};
	t_m.j = (t_vec3) {0, cos(theta), sin(theta), 0};
	t_m.k = (t_vec3) {0, -sin(theta), cos(theta), 0};
	t_m.p = (t_vec3) {9, 4, 23, 1};

	printf("transformation matrix\n");
	print_matrix(t_m);
	printf("inverse matrix\n");
	i_m = mat_inverse(t_m);
	print_matrix(i_m);

	t_data	scene;
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
