/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/13 02:17:09 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

int	rt_scene_init(t_data *scene, char **av)
{
//	int	i;

//	ft_bzero(scene, sizeof(t_data));
   // if (ac < 1)
   // 	return (1);
   // else if (ac > 1)
   	scene->map_name = av[1];
	gettimeofday(&scene->start, NULL);
	scene->res = 5;
	scene->processing = 1;
	scene->print = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	scene->announce = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	scene->painter_rest = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	scene->master_rest = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	scene->cam.yaw = 90.0f;
	scene->cam.fov = -1;
	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.h = 1;
	scene->viewport.w = 1;
 //   i = -1;
 //   while (++i < 99999)
 //   	scene->key_state[i] = 0;
 //   //scene->viewport.w = calc_vp_width(53, 2);
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

int	rt_init(t_data *scene, char **av)
{
	t_img	*img;
	int		status;

	status = 0;
	status = rt_scene_init(scene, av);
	mlx_tozero(scene);
	img = &scene->img;
	if (!status)
		scene->mlx = mlx_init();
	if (!scene->mlx && !status)
		status = -11;
	else if (!status)
		scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Hazardous RAY TRACER");
	if (!scene->win && !status)
		status = -12;
	else if (!status)
		img->ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!img->ptr && !status)
		status = -13;
	else if (!status)
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen, &img->endian);
	if (!img->addr && !status)
		status = -14;
	return (status);
}

void	init_obj(t_object *obj, t_type type)
{
	ft_bzero(obj, sizeof(t_object));
	obj->type = type;
	obj->t_m = mat_init_id();
	obj->spec = SPECULAR;
}
