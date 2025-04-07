/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/26 17:59:08 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	rt_scene_tozero(t_data *scene)
{
	scene->selected = NULL;
	scene->res = 5;
	scene->cam.pos = (t_vec3){0, 0, 0, 0};
	scene->cam.dir = (t_vec3){0, 0, 1, 0};
	scene->cam.up = (t_vec3){0, 1, 0, 0};
	scene->cam.right = (t_vec3){1, 0, 0, 0};
	scene->cam.yaw = 90.0f;
	scene->cam.pitch = 0.0f;
	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.h = 1;
	scene->viewport.w = 1; 
	//scene->viewport.w = calc_vp_width(53, 2);
	scene->objects = NULL;
	scene->lights = NULL;
	scene->selected = NULL;
	return (0);
}

void	mlx_tozero(t_data *scene)
{
	int	i;

	scene->mlx = NULL;
	scene->win = NULL;
	//ft_bzero(&scene->img,sizeof(t_img));
	//scene->img.ptr = NULL;
	//scene->img.addr = NULL;
	i = -1;
	while (++i < 99999)
		scene->key_state[i] = 0;
}

int	rt_init(t_data *scene)
{
	//int	i;
	t_img	*img;
	int		status;

	status = rt_scene_tozero(scene);
	mlx_tozero(scene);
	img = &scene->img;
	scene->mlx = mlx_init();
	if (!scene->mlx)
		status = -1;
	else
		scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Ray_tracing");
	if (!scene->win)
		status = -1;
	else if (!status)
		img->ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!img->ptr)
		status = -1;
	else if (!status)
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen, &img->endian);
	if (!img->addr)
		status = -1;
	return (status);
}
