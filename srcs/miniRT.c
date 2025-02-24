#include <miniRT.h>

int	rt_shut_down(t_data *scene)
{
	mlx_clear_window(scene->mlx, scene->win);
	mlx_destroy_window(scene->mlx, scene->win);
	//mlx_destroy_display(scene->mlx);
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
	int x;
	int y;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			rt_put_pixel(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	rt_lighton(t_circle origin, t_circle object, t_img *img)
{
	int	i;
	float	angle;
	t_ray ray[RAY_NUMBER];

	angle = (M_PI * 2) / RAY_NUMBER;
	i = 0;
	while (i < RAY_NUMBER)
	{
		ray[i].origin = origin.pos;
		//ray[i].lenght = 550;
		ray[i].angle = i * angle;
		//ray[i].end.x = origin.pos.x + ray[i].lenght * (cos(ray[i].angle));
		//ray[i].end.y = origin.pos.y + ray[i].lenght * (sin(ray[i].angle));
		ray[i].thickness = 10;
		rt_ray(ray[i], object, img);
		i++;
	}
}

int	render(t_data *scene)
{
	rt_clear_window(&scene->img);
	if (scene->mouse_state)
	{
		scene->circle.pos = scene->mouse;
		rt_lighton(scene->circle, scene->object, &scene->img); 
	}
	printf("drawing\n");
	rt_circle(scene->circle, &scene->img); 
	rt_circle(scene->object, &scene->img);
	//rt_rect(scene->rect, &scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	return (0);
}

int	main()
{
t_data	scene;

	scene.rect.size.x = 50;
	scene.rect.size.y = 80;
	scene.rect.pos.x = 200;
	scene.rect.pos.y = 200;
	scene.circle.radius = 30;
	scene.circle.pos.x = 400;
	scene.circle.pos.y = 400;
	scene.object.radius = 70;
	scene.object.pos.x = 500;
	scene.object.pos.y = 500;

	if (rt_init(&scene))
		return (1);
	mlx_hook(scene.win, 2, 1L << 0, &key_press, &scene);
	mlx_hook(scene.win, 3, 1L << 1, &key_release, &scene);
	mlx_hook(scene.win, 4, 1L << 2, &mouse_press, &scene);
	mlx_hook(scene.win, 5, 1L << 3, &mouse_release, &scene);
	mlx_hook(scene.win, 6, 1L << 6, &mouse_pos, &scene);
	mlx_hook(scene.win, 17, 1L << 2, &rt_shut_down, &scene);

	mlx_loop_hook(scene.mlx, &render, &scene);
	mlx_loop(scene.mlx);

	ft_printf("yeah!\n");
	return (0);
}
