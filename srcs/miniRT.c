#include <miniRT.h>

int	rt_shut_down(t_data *scene)
{
	mlx_clear_window(scene->mlx, scene->win);
	mlx_destroy_window(scene->mlx, scene->win);
	free(scene->mlx);
	return (0);
}

int	rt_init(t_data *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (1);
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Hello world!");
	if (!scene->win)
		return (1);
	scene->img.ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->img.ptr)
		return (1);
	scene->img.addr = mlx_get_data_addr(scene->img.ptr, &scene->img.bpp, &scene->img.llen, &scene->img.endian);
	if (!scene->img.addr)
		return (1);
	return (0);
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

int	main()
{
	t_data	scene;
	if (rt_init(&scene))
		return (1);

	scene.sphere = malloc(sizeof(t_sphere) * 1);
	scene.sphere->radius = 2;
	scene.sphere->pos.x = 2;
	scene.sphere->pos.y = 0;
	scene.sphere->pos.z = 30;
	scene.sphere->color = 0x37FF05FF;
	scene.sphere->next = NULL;
	scene.camera.z = 0;
	scene.camera.y = 0;
	scene.camera.x = 0;
	scene.cnv.w = WIDTH;
	scene.cnv.h = HEIGHT;
	scene.viewport.pos.x = 1;
	scene.viewport.pos.y = 1;
	scene.viewport.pos.z = 1;
	scene.viewport.h = 1;
	scene.viewport.w = 1;
	//display_color(&scene.img, scene.cam, scene.cnv, scene.viewport, &scene);
	mlx_hook(scene.win, 2, 1L << 0, &key_press, &scene);
	mlx_hook(scene.win, 3, 1L << 1, &key_release, &scene);
	mlx_hook(scene.win, 4, 1L << 2, &mouse_press, &scene);
	mlx_hook(scene.win, 5, 1L << 3, &mouse_release, &scene);
	mlx_hook(scene.win, 6, 1L << 6, &mouse_pos, &scene);
	mlx_hook(scene.win, 17, 1L << 2, &rt_shut_down, &scene);
	mlx_loop_hook(scene.mlx, &render, &scene);
	mlx_loop(scene.mlx);
	printf("Finish!\n");
	return (0);
}
