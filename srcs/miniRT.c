/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:01:43 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/02 16:25:27 by jhervoch         ###   ########.fr       */
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
	mlx_hook(scene->win, 17, 1L << 2, &rt_shut_down, scene);
	mlx_loop_hook(scene->mlx, &render, scene);
	mlx_loop(scene->mlx);
	return (0);
}

void	select_object(t_data *scene)
{
	t_ray		catch_ray;
	t_painter	*painter;
	t_canvas	cnv;
	t_viewport	vp;

	scene->selected = NULL;
	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = scene->mouse.x - (cnv.w / 2.0f);
	cnv.loc.y = (cnv.h / 2.0f) - scene->mouse.y;
	catch_ray.d = get_viewport_loc(cnv, vp);
	catch_ray.d = apply_camera_rotation(scene->cam, catch_ray.d);
	catch_ray.o = scene->cam.pos;
	painter = &((t_painter){0.001f, T_MAX, R_LIMIT, catch_ray, scene});
	scene->selected = closest_intersect(painter, 0, scene->objects);
}

int	main(int ac, char **av)
{
	int			status;
	t_data		scene;

	ft_bzero(&scene, sizeof(t_data));
	print_input();
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
