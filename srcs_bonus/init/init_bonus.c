/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:42:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 14:15:30 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>
t_painter	th_painter_init(t_data *scene, int i)
{
	t_painter	new;

	ft_bzero(&new, sizeof(new));
	new.sceneref = (t_data *)scene;
	new.id = i + 1;
	return (new);
}

int	rt_scene_init(t_data *scene, char **av, int ac)
{
	if (ac < 2)
	{
		printf("test:%d", ac);
		return (11);
	}
	else if (ft_strlen(av[1]) <= 3)
		return (12);
	else if (ft_strcmp(av[1] + ft_strlen(av[1]) - 3, ".rt"))
		return (13);
	else if (!ft_strcmp(av[1] + ft_strlen(av[1]) - 4, "/.rt"))
		return (14);
	ft_bzero(scene, sizeof(t_data));
	scene->map_name = av[1];
	gettimeofday(&scene->start, NULL);
	scene->res = 5;
	scene->processing = 1;
	scene->print = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	scene->announce = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	scene->painter_rest = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	scene->master_rest = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	scene->cam.yaw = 90.0f;
	scene->cam.fov = -1; //input to get// return status
	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.h = 1;
	scene->viewport.w = 1;
	scene->painter = th_painter_init(scene, 0);
	return (0);
}

int	rt_init(t_data *scene, char **av, int ac)
{
	t_img	*img;

	scene->status = rt_scene_init(scene, av, ac);
	img = &scene->img;
	if (!scene->status)
		scene->mlx = mlx_init();
	if (!scene->mlx && !scene->status)
		scene->status = 21;
	else if (!scene->status)
		scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "RT");
	if (!scene->win && !scene->status)
		scene->status = 22;
	else if (!scene->status)
		img->ptr = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!img->ptr && !scene->status)
		scene->status = 23;
	else if (!scene->status)
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen,
				&img->endian);
	if (!img->addr && !scene->status)
		scene->status = 24;
	return (scene->status);
}

void	init_obj(t_object *obj, t_type type)
{
	ft_bzero(obj, sizeof(t_object));
	obj->type = type;
	obj->t_m = mat_init_id();
	obj->spec = SPECULAR;
}
