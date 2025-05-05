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

void	print_timestamp(struct timeval *last_time, t_data *scene)
{
	const char	*title = "ms per frame: ";
	char		str[20];
	int			time;
	int			len;
	int			i;

	time = time_from(last_time) / 1000;
	len = get_intlen(time, 10);
	i = 0;
	while (i < len)
	{
		str[len - i - 1] = (time % 10) + '0';
		time = time / 10;
		i++;
	}
	str[len] = '\0';
	mlx_string_put(scene->mlx, scene->win, 10, 10, 0, (char *)title);
	mlx_string_put(scene->mlx, scene->win, 90, 10, 0, str);
}

int	rt_multi_thread(t_data *scene)
{
	struct timeval	last_time;
	const t_vec2	pos = {0, 0};
	t_painter		master;
	//char			*str;
	//char			*tmp;

	master = th_painter_init(scene, -1);
	gettimeofday(&last_time, NULL);	// Timestamp 
	pthread_mutex_lock(&scene->print);
	th_annouce("Master wait\n", &master);
	while (scene->at_rest < THREAD_NB)							// wait until all thread are done (scene->at_rest)	
		pthread_cond_wait(&scene->master_rest, &scene->print);	
	pthread_mutex_unlock(&scene->print);
	th_annouce("Master start\n", &master);
	rt_rect(&scene->img, pos, (t_vec2){150, 20}, 0xFFFFFFFF);	
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	handle_input(scene);
	print_timestamp(&last_time, scene);
	scene->at_rest = 0;											// set at_rest = 0 to unlock thread "painters"
	th_annouce("Master DONE\n", &master);
	pthread_cond_broadcast(&scene->painter_rest);				// send signal to unlock them
	pthread_mutex_unlock(&scene->print);
	return (0);
}

int	rt_mono_thread(t_data *scene)
{
	struct timeval	last_time;
	const t_vec2	pos = {0, 0};
	t_painter		painter;

	gettimeofday(&last_time, NULL);
	painter = th_painter_init(scene, 0);
	display_color(&painter);
	rt_rect(&scene->img, pos, (t_vec2){150, 20}, 0xFFFFFFFF);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	handle_input(scene);
	print_timestamp(&last_time, scene);
	return (0);
}

void	rt_rect(const t_img *img, t_vec2 pos, t_vec2 size, int color)
{
	int	i;
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

int	main(int ac, char **av, char **envp)
{
	t_data		scene;
	t_painter	painter;

	(void)envp;
	if (!envp)
	{
		printf("no environnemnt\n");
		return (0);
	}
	ft_bzero(&scene, sizeof(t_data));
	if (ac > 3 || ft_strlen(av[1]) <= 3
		|| ft_strcmp(av[1] + ft_strlen(av[1]) - 3, ".rt")
		|| !ft_strcmp(av[1] + ft_strlen(av[1]) - 4, "/.rt"))
		print_error_msg(-9, &scene);
	print_input();
	scene.status = rt_init(&scene, av);
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
