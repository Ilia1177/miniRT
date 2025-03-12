#include <miniRT.h>

int		rt_shut_down(t_data *scene)
{
	free_sphere(scene->sphere);
	free_light(scene->light);
	mlx_destroy_image(scene->mlx, scene->img.ptr);
	//mlx_clear_window(scene->mlx, scene->win);
	mlx_destroy_window(scene->mlx, scene->win);
//	mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	exit(0);
	return (0);
}

int		rt_init(t_data *scene, int *status)
{
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
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

int	scene_init(t_data *scene)
{


	scene->cam.pos =	init_vec3(0, 0, 0);
	scene->cam.dir =	init_vec3(0, 0, 1);
	scene->cam.up =		init_vec3(0, 1, 0);
	scene->cam.right =	init_vec3(1, 0, 0);
	
	scene->cam.yaw =	0.0f;
	scene->cam.pitch =	0.0f;
	
	scene->viewport.h = 1; 
	scene->viewport.w = 1; 
//	scene->cam.pos.z = 0;
//	scene->cam.pos.y = 0;
//	scene->cam.pos.x = 0;
	scene->light = NULL;
	scene->sphere = NULL;
//	scene->cam.dir= (t_vec3){0, 0, 1};
//	scene->cam.up = (t_vec3){0, 1, 0};
//	scene->cam.right = (t_vec3){1, 0, 0};
//	scene->cam.yaw = 80.0f;  // Looking straight along +Z
//    scene->cam.pitch = -10.0f;
//	scene->cnv.w = WIDTH;
//	scene->cnv.h = HEIGHT;
//	scene->viewport.pos.x = 1;
//	scene->viewport.pos.y = 1;
//	scene->viewport.pos.z = 1;
//	scene->viewport.h = 1;
//	scene->viewport.w = 1;	
//	scene->sphere = malloc(sizeof(t_sphere) * 1);
//	scene->sphere->radius = 1;
//	scene->sphere->pos.x = -1;
//	scene->sphere->pos.y = 2;
//	scene->sphere->pos.z = 20;
//	scene->sphere->color = 0xFF3255a4;
//	scene->sphere->specular = 10;
//	scene->sphere->reflective = 0.2;
//	//scene->sphere->next = NULL;
//	scene->sphere->next = malloc(sizeof(t_sphere) * 1);
//	scene->sphere->next->radius = 1;
//	scene->sphere->next->pos.x = 1;
//	scene->sphere->next->pos.y = 2;
//	scene->sphere->next->pos.z = 20;
//	scene->sphere->next->color = 0xFF00838a;
//	scene->sphere->next->specular = 1000;
//	scene->sphere->next->reflective = 0.7;
//	//scene->sphere->next->next = NULL;
//	scene->sphere->next->next = malloc(sizeof(t_sphere) * 1);
//	scene->sphere->next->next->radius = 8000;
//	scene->sphere->next->next->pos.x = -7;
//	scene->sphere->next->next->pos.y = -8001;
//	scene->sphere->next->next->pos.z = -20;
//	scene->sphere->next->next->color = 0xFF00838a;
//	scene->sphere->next->next->specular = 1000;
//	scene->sphere->next->next->next = NULL;
//
//	scene->light = malloc(sizeof(t_light) * 1);
//	scene->light->type = DIRECTIONAL;
//	scene->light->intensity = 0.5;
//	scene->light->dir.x = 0;
//	scene->light->dir.y = 2;
//	scene->light->dir.z = 0;
//	scene->light->next = NULL;
//	scene->light->next = malloc(sizeof(t_light) * 1);
//	scene->light->next->type = AMBIENT;
//	scene->light->next->intensity = 0.7;
//	scene->light->next->dir.x = 2;
//	scene->light->next->dir.y = 2;
//	scene->light->next->dir.z = 2;
//	scene->light->next->next = NULL;

//	scene->light->next->next = malloc(sizeof(t_light) * 1);
//	scene->light->next->next->type = AMBIENT;
//	scene->light->next->next->intensity = 0.2;
//	scene->light->next->next->pos.x = 3;
//	scene->light->next->next->pos.y = 3;
//	scene->light->next->next->pos.z = 3;
//	scene->light->next->next->next = NULL;
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
	if (ac > 1)
		scene.map_name = av[1];
	if (rt_init(&scene, &status))
		return (status);

	
//	while (1)
//	{
//		input = get_next_lines(0);
//		parse_input(input);
//		free(input);
//	}
//
	status = scene_init(&scene);
	if (!status)
		status = build_scene(&scene);
	printf("status: %d\n", status);
	if (!status)
		display_scene(&scene);
//	mlx_hook(scene.win, 2, 1L << 0, &key_press, &scene);
//	mlx_hook(scene.win, 3, 1L << 1, &key_release, &scene);
//	mlx_hook(scene.win, 4, 1L << 2, &mouse_press, &scene);
//	mlx_hook(scene.win, 5, 1L << 3, &mouse_release, &scene);
//	mlx_hook(scene.win, 6, 1L << 6, &mouse_pos, &scene);
//	mlx_hook(scene.win, 17, 1L << 2, &rt_shut_down, &scene);
//	mlx_loop_hook(scene.mlx, &render, &scene);
//	mlx_loop(scene.mlx);
	return (0);
}
