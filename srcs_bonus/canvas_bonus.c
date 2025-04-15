#include <miniRT_bonus.h>

// get location of the point in the viemport from canvas'location
t_vec4 throught_vp(t_canvas cnv, t_viewport vp)
{
	t_vec4 dir;

	dir.x = cnv.loc.x * vp.w / cnv.w;
	dir.y = cnv.loc.y * vp.h / cnv.h;
	dir.z = 1;
	dir.w = 0;
	return (dir);
}

// get screen's pixel from canvas's point
t_vec2 cnv_to_screen(t_canvas cnv)
{
	t_vec2 screen;

	screen.x = (cnv.w / 2) + cnv.loc.x;
	screen.y = (cnv.h / 2) - cnv.loc.y;
	return (screen);
}

void	color_screen(t_img *img, int x, int y, int res, t_argb color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < res)
	{
		j = -1;
		while (++j < res)
		{
			rt_put_pixel(img, x + i, y + j, encode_argb(color));
		}
	}
}

// throw ray for every point of the canvas
void	display_color(t_painter *painter)
{
	t_data			*scene;
	t_vec2			pix;
	char		res;

	scene = painter->sceneref;
	res = scene->res;
	ft_bzero(&painter->ray, sizeof(t_ray));
	painter->lim[0] = 1.0f;
	painter->lim[1] = T_MAX;
	painter->lim[2] = R_LIMIT;

	painter->cnv.loc.x = (-painter->cnv.w / 2) + ((painter->id-1) * (painter->cnv.w / THREAD_NB));
	while (painter->cnv.loc.x < (painter->id) * (painter->cnv.w / THREAD_NB) )
	{
		painter->cnv.loc.y = -painter->cnv.h / 2;
		while (painter->cnv.loc.y < (painter->cnv.h / 2))
		{
			painter->ray.o = scene->cam.t_m.p;
			painter->ray.d = throught_vp(painter->cnv, painter->vp);
			painter->ray.d = normalize_vec4(mat_apply(scene->cam.t_m, painter->ray.d));
			painter->color = throw_ray(painter);
			pix = cnv_to_screen(painter->cnv);
			color_screen(&scene->img, pix.x, pix.y, res, painter->color);
			painter->cnv.loc.y += res;
		}
		painter->cnv.loc.x += res;
	}
}
