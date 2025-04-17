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
int	rt_multi_thread(t_data *scene)
{
	struct timeval last_time;
	char	*str;
	char	*tmp;
	const t_vec2 pos = {0, 0};

	gettimeofday(&last_time, NULL);
    pthread_mutex_lock(&scene->print);
    while (scene->at_rest < THREAD_NB) {
        pthread_cond_wait(&scene->master_rest, &scene->print);
    }
	pthread_mutex_unlock(&scene->print);
	rt_rect(&scene->img, pos, (t_vec2){110, 20}, 0xFFFFFFFF);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	handle_input(scene);
	str = 0;
	tmp = ft_itoa((int)time_from(&last_time) / 1000);
	if (tmp)
		str = ft_strjoin("MS per frame:", tmp);
	if (str)
		mlx_string_put(scene->mlx, scene->win, 10, 10, 0, str);
	free(str);
	free(tmp);
	scene->at_rest = 0;
    pthread_cond_broadcast(&scene->painter_rest);
    pthread_mutex_unlock(&scene->print);
//	if (!scene->processing)
//		mlx_loop_end(scene->mlx);
	return (0);
}
int rt_mono_thread(t_data *scene)
{
	struct timeval last_time;
	char	*str;
	char	*tmp;
	const	t_argb color = {255, 245, 47, 187};
	const	t_vec2 pos = {0, 0};
	t_painter painter;

	gettimeofday(&last_time, NULL);
	painter = th_painter_init(scene, 0);
	display_color(&painter);
	rt_rect(&scene->img, pos, (t_vec2){110, 20}, 0xFFFFFFFF);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	handle_input(scene);
	str = 0;
	tmp = ft_itoa((int)time_from(&last_time) / 1000);
	if (tmp)
		str = ft_strjoin("MS per frame:", tmp);
	if (str)
		mlx_string_put(scene->mlx, scene->win, 10, 10, 0, str);
	free(str);
	free(tmp);
//	if (!scene->processing)
//		mlx_loop_end(scene->mlx);
	return (0);
}

void	rt_rect(t_img *img, t_vec2 pos, t_vec2 size, int color)
{
	int i;
	int	j;

	i = -1;
	while (++i < size.x)
	{
		j = -1;
		while (++j < size.y)
			rt_put_pixel(img, pos.x + i, pos.y + j, color);
	}
}

int	display_scene(t_data *scene)
{
	mlx_hook(scene->win, 2, 1L << 0, &key_press, scene);
	mlx_hook(scene->win, 3, 1L << 1, &key_release, scene);
	mlx_hook(scene->win, 17, 1L << 2, &rt_shut_down, scene);
	mlx_hook(scene->win, 4, 1L << 2, &mouse_press, scene);
	mlx_hook(scene->win, 5, 1L << 3, &mouse_release, scene);
	mlx_hook(scene->win, 6, 1L << 6, &mouse_pos, scene);
	if (THREAD_NB == 1)
	{
		printf("starting mono-thread RT\n");
		mlx_loop_hook(scene->mlx, &rt_mono_thread, scene);

	}
	else if (THREAD_NB > 1)
	{
		printf("Start multi-thread RT\n");
		mlx_loop_hook(scene->mlx, &rt_multi_thread, scene);
		scene->status = th_painter_start(scene);
		if (!scene->status)
			th_master_start(scene);
		else
			rt_shut_down(scene);
	}
	if (!scene->status)
		mlx_loop(scene->mlx);
	return (scene->status);
}

int	main(int ac, char **av)
{
	t_data		scene;
	t_painter	painter;

	scene.status = rt_init(&scene, ac, av);
	if (!scene.status)
		scene.status = build_scene(&scene);
	if (scene.status)
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
	return (scene.status);
}

