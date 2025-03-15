#include <miniRT.h>

/* int		rt_shut_down(t_data *scene) */
/* { */
/* 	free_sphere(scene->sphere); */
/* 	free_light(scene->light); */
/* 	mlx_destroy_image(scene->mlx, scene->img.ptr); */
/* 	//mlx_clear_window(scene->mlx, scene->win); */
/* 	mlx_destroy_window(scene->mlx, scene->win); */
/* //	mlx_destroy_display(scene->mlx); */
/* 	free(scene->mlx); */
/* 	exit(0); */
/* 	return (0); */
/* } */

int	rt_shut_down(t_data *scene)
{
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->img.ptr)
		mlx_destroy_image(scene->mlx, scene->img.ptr);
	//if (scene->img.ptr)
	//	mlx_destroy_image(scene->mlx, scene->img.ptr);
	if (scene->mlx)
	{
		//mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	exit(0);
}

int		rt_init(t_data *scene, int *status)
{
	int i;

	*status = 0;
	scene->mlx = mlx_init();
	if (!scene->mlx)
		*status = 1;
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Ray_tracing");
	if (!status && !scene->win)
		*status = 1;
	scene->img.ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!status && !scene->img.ptr)
		*status = 1;
	scene->img.addr = mlx_get_data_addr(scene->img.ptr, &scene->img.bpp, &scene->img.llen, &scene->img.endian);
	if (!status && !scene->img.addr)
		*status = 1;
	i = -1;
	while (++i < 99999)
		scene->key_state[i] = 0;
	return (*status);
}

void	rt_clear_window(t_img *img)
{
	t_vec2	pix;

	pix.y = 0;
	while (pix.y < HEIGHT)
	{
		pix.x = 0;
		while (pix.x < WIDTH)
		{
			rt_put_pixel(img, pix, 0x00000000);
			pix.x++;
		}
		pix.y++;
	}
}

int	render(t_data *scene)
{
	handle_input(scene);
	rt_clear_window(&scene->img);
	display_color(scene);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	return (0);
}

t_vec3	init_vec3(float x, float y, float z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
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
	if (ac > 1)
		scene.map_name = av[1];
	if (rt_init(&scene, &status))
		return (status);
	status = scene_init(&scene);
	if (!status)
		display_scene(&scene);
	return (0);
}
