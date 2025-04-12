#include <miniRT_bonus.h>

void *draw_start(void *slv)
{
	t_slave *slave;
	t_data	*scene;

	slave = (t_slave *)slv;
	scene = slave->sceneref;
	mlx_loop(scene->mlx);
	return NULL;
}

void	rt_thread_quit(t_data *scene)
{
	return ;
}

int	rt_render(t_slave *slave)
{
	t_data *scene;

	scene = slave->sceneref;
	handle_input(scene);
	display_color(scene, slave);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	return (0);
}
t_slave	slave_init(t_data *scene, int i)
{
	t_slave new;

	new.cnv = scene->cnv;
	new.vp = scene->viewport;
	new.sceneref = (t_data *)scene;
	new.id = i + 1;
	return (new);
}

int	rt_thread_start(t_data *scn)
{
	pthread_t	master;
	t_data		*scene;
	int	i;

	scene = scn;
	i = 0;
	while (i < THREAD_NB)
	{
		scene->slave[i] = slave_init(scene, i);
		if (pthread_create(&scene->slave[i].itself, NULL, draw_start, &scene->slave[i]))
		{
			rt_thread_quit(scene);
			return (1);
		}
		i++;
	}
	i = -1;
	while (++i < THREAD_NB)
		pthread_join(scene->slave[i].itself, NULL);
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
	mlx_loop_hook(scene->mlx, &rt_render, scene->slave);
	rt_thread_start(scene);
//	mlx_loop(scene->mlx);
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
