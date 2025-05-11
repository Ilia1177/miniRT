/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:54:15 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/11 11:20:48 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

int	rt_render(t_data *scene)
{
	static int		first_rend;
	struct timeval	last_time;
	const t_vec2	pos = {0, 0};

	if (!first_rend || scene->rend)
	{
		gettimeofday(&last_time, NULL);
		handle_input(scene);
		display_color(&scene->painter);
		rt_rect(&scene->img, pos, (t_vec2){150, 20}, 0xFFFFFFFF);
		mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
		print_timestamp(&last_time, scene);
		first_rend = 1;
	}
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
	mlx_loop_hook(scene->mlx, &rt_render, scene);
	mlx_loop(scene->mlx);
	return (scene->status);
}

int	main(int ac, char **av, char **envp)
{
	t_data		scene;
	t_painter	painter;

	if (!envp)
		scene.status = 99;
	if (!scene.status)
		scene.status = rt_init(&scene, av, ac);
	if (!scene.status)
		scene.status = build_scene(&scene);
	if (scene.status)
		print_error_msg(scene.status, &scene);
	else if (ac == 3)
	{
		scene.res = 1;
		display_color(&painter);
		save_as_ppm(&scene.img, av[2]);
		rt_shut_down(&scene);
	}
	else if (ac == 2)
	{
		print_input();
		display_scene(&scene);
	}
	return (scene.status);
}
