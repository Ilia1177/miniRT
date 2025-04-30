/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:01:43 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/29 18:22:18 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	render(t_data *scene)
{
	if (scene->rend)
	{
		handle_input(scene);
		display_color(scene);
		mlx_put_image_to_window(scene->mlx, scene->win, scene->img.ptr, 0, 0);
	}
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
	int			status;
	t_data		scene;

	ft_bzero(&scene, sizeof(t_data));
	if (ac != 2 || ft_strlen(av[1]) <= 3
		|| ft_strcmp(av[1] + ft_strlen(av[1]) - 3, ".rt")
		|| !ft_strcmp(av[1] + ft_strlen(av[1]) - 4, "/.rt"))
		print_error_msg(-9, &scene);
	scene.map_name = av[1];
	status = rt_init(&scene);
	if (!status)
		status = build_scene(&scene);
	display_scene(&scene);
	return (status);
}
