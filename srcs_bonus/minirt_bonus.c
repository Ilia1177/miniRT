/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:54:15 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/12 15:28:50 by npolack          ###   ########.fr       */
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
