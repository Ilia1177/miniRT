/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:35:26 by npolack           #+#    #+#             */
/*   Updated: 2025/05/05 16:35:13 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// get screen's pixel from canvas's point
t_vec2	cnv_to_screen(t_vec2 cnv)
{
	t_vec2	screen;

	screen.x = (WIDTH / 2) + cnv.x;
	screen.y = (HEIGHT / 2) - cnv.y;
	return (screen);
}

void	painter_reset(t_painter *painter, t_vec2 cnv)
{
	const t_data	*scene = painter->sceneref;

	painter->lim[0] = EPSILON;
	painter->lim[1] = T_MAX;
	painter->lim[2] = R_LIMIT;
	painter->ray.o = scene->cam.t_m.p;
	painter->ray.d = projection(cnv, (t_data *) scene);
	painter->ray.d = normalize_vec4(mat_apply(scene->cam.t_m, painter->ray.d));
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
// throw ray for every pixel of the canvas
void	display_color(t_painter *painter)
{
	const t_data	*scene = painter->sceneref;
	const char		res = scene->res;
	t_vec2			pix;
	t_vec2			cnv;
	t_argb			color;

	ft_bzero(&painter->ray, sizeof(t_ray));
	cnv.x = -WIDTH / 2;
	while (cnv.x < WIDTH)
	{
		cnv.y = -HEIGHT / 2;
		while (cnv.y < (HEIGHT / 2))
		{
			painter_reset(painter, cnv);
			color = throw_ray(painter);
			pix = cnv_to_screen(cnv);
			rt_rect(&scene->img, pix, (t_vec2){res, res}, argb_toint(color));
			cnv.y += res;
		}
		cnv.x += res;
	}
}
