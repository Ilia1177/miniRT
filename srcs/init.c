/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/29 18:28:17 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	rt_scene_tozero(t_data *scene)
{
	scene->res = 5;
	scene->cam.pos = (t_vec4){0, 0, 0, 0};
	scene->cam.dir = (t_vec4){0, 0, 1, 0};
	scene->cam.up = (t_vec4){0, 1, 0, 0};
	scene->cam.right = (t_vec4){1, 0, 0, 0};
	scene->cam.yaw = 90.0f;
	scene->cam.pitch = 0.0f;
	scene->cam.fov = -1;
	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.h = 1;
	scene->viewport.w = calc_vp_width(53, 2);
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
	i = -1;
	while (++i < 99999)
		scene->key_state[i] = 0;
}

int	rt_init(t_data *scene)
{
	t_img	*img;
	int		status;

	status = rt_scene_tozero(scene);
	mlx_tozero(scene);
	img = &scene->img;
	scene->mlx = mlx_init();
	if (!scene->mlx)
		status = -11;
	else
		scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Ray_tracing");
	if (!scene->win)
		status = -12;
	else if (!status)
		img->ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!img->ptr)
		status = -13;
	else if (!status)
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
				&img->llen, &img->endian);
	if (!img->addr)
		status = -14;
	return (status);
}

void	init_painter(t_painter *painter, t_data *scene, t_ray *ray)
{
	ft_bzero(painter, sizeof(painter));
	painter->scene = scene;
	if (ray)
		painter->ray = *ray;
}

void	reset_painter(t_painter *painter, t_canvas cnv)
{
	t_data		*scene;
	t_viewport	vp;

	if (painter)
	{
		scene = painter->scene;
		vp = scene->viewport;
		painter->tmin = 1.0f;
		painter->tmax = T_MAX;
		painter->rec = R_LIMIT;
		painter->ray.o = scene->cam.pos;
		painter->ray.d = get_viewport_loc(cnv, vp);
		painter->ray.d = apply_camera_rotation(scene->cam, painter->ray.d);
	}
}
