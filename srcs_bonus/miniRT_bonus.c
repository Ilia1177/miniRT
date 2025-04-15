#include <miniRT_bonus.h>

long long	time_from(struct timeval *last)
{
	struct timeval	current_time;
	long long		sec;
	long long		usec;

	gettimeofday(&current_time, NULL);
	sec = current_time.tv_sec - last->tv_sec;
	usec = current_time.tv_usec - last->tv_usec;
	return ((sec * 1000000LL) + (usec));
}

int rt_render(t_data *scene)
{

	struct timeval last_time;

	gettimeofday(&last_time, NULL);
//	printf("mastering: wait\n");
    pthread_mutex_lock(&scene->print);
    while (scene->at_rest < THREAD_NB) {
        pthread_cond_wait(&scene->master_rest, &scene->print);
    }
	pthread_mutex_unlock(&scene->print);
//	printf("mastering: start\n");
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	handle_input(scene);
	scene->at_rest = 0;
//	printf("mastering: end / broadcast painters\n");
    pthread_cond_broadcast(&scene->painter_rest);
    pthread_mutex_unlock(&scene->print);
	printf("TS: %02lld ms\n", time_from(&last_time) / 1000);
    return 0;
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
		th_master_start(scene);
	else
		rt_shut_down(scene);
	return (0);
}

int	main(int ac, char **av)
{
	int status;
	t_data	scene;
	t_painter	painter;

	status = rt_init(&scene, ac, av);
	if (!status)
		status = build_scene(&scene);
	if (status)
		free_data(&scene);
	else if (ac == 3)
	{
		scene.res = 1;
		display_color(&painter);
		save_as_ppm(&scene.img, av[2]);
		rt_shut_down(&scene);
	}
	else if (ac == 2)
		display_scene(&scene);
	return (status);
}

