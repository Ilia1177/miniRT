/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/10 16:31:31 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

int	rt_scene_init(t_data *scene, int ac, char **av)
{
	int	i;

	ft_bzero(scene, sizeof(t_data));
	if (ac < 1)
		return (1);
	else if (ac > 1)
		scene->map_name = av[1];
	scene->res = 20;
	scene->cam.yaw = 90.0f;
	scene->cam.pitch = 0.0f;
	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.h = 1;
	scene->viewport.w = 1; 
	i = -1;
	while (++i < 99999)
		scene->key_state[i] = 0;
	//scene->viewport.w = calc_vp_width(53, 2);
	return (0);
}


int	rt_init(t_data *scene, int ac, char **av)
{
	t_img	*img;
	int		status;

	if (rt_scene_init(scene, ac, av))
		return (12);
	status = 0;
	img = &scene->img;
	scene->mlx = mlx_init();
	if (!scene->mlx)
		status = -1;
	else if (!status)
		scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Ray_tracing");
	if (!scene->win && !status)
		status = -2;
	else if (!status)
		img->ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!img->ptr && !status)
		status = -3;
	else if (!status)
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen, &img->endian);
	if (!img->addr && !status)
		status = -4;
	return (status);
}
