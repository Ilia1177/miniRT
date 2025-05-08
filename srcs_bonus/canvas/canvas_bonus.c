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

// get location of the point in the viemport from canvas'location
t_vec4	throught_vp(t_vec2 cnv, t_viewport vp)
{
	t_vec4	dir;

	dir.x = (float)cnv.x * vp.w / WIDTH;
	dir.y = (float)cnv.y * vp.h / HEIGHT;
	dir.z = vp.pos.z;
	dir.w = 0.0f;
	dir = normalize_vec4(dir);
	return (dir);
}

// get screen's pixel from canvas's point
t_vec2	cnv_to_screen(t_vec2 cnv)
{
	t_vec2	screen;

	screen.x = (WIDTH / 2) + cnv.x;
	screen.y = (HEIGHT / 2) - cnv.y;
	return (screen);
}

void	reset_painter(t_painter *painter, t_vec2 cnv)
{
	const t_data	*scene = painter->sceneref;

	painter->lim[0] = 1.0f;
	painter->lim[1] = T_MAX;
	painter->lim[2] = R_LIMIT;
	painter->ray.o = scene->cam.t_m.p;
	painter->ray.d = throught_vp(cnv, scene->viewport);
	painter->ray.d = normalize_vec4(mat_apply(scene->cam.t_m, painter->ray.d));
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
			reset_painter(painter, cnv);
			color = throw_ray(painter);
			pix = cnv_to_screen(cnv);
			rt_rect(&scene->img, pix, (t_vec2){res, res}, encode_argb(color));
			cnv.y += res;
		}
		cnv.x += res;
	}
}
