#include <miniRT_bonus.h>

// get location of the point in the viemport from canvas'location
t_vec4 throught_vp(t_vec2 cnv, t_viewport vp)
{
	t_vec4 dir;

	dir.x = (float)cnv.x * vp.w / WIDTH;
	dir.y = (float)cnv.y * vp.h / HEIGHT;
	dir.z = 1.0f;
	dir.w = 0;
	dir = normalize_vec4(dir);
	return (dir);
}

// get screen's pixel from canvas's point
t_vec2 cnv_to_screen(t_vec2 cnv)
{
	t_vec2 screen;

	screen.x = (WIDTH / 2) + cnv.x;
	screen.y = (HEIGHT / 2) - cnv.y;
	return (screen);
}
void	reset_painter(t_painter *painter, t_vec2 cnv)
{
	t_data	*scene;

	scene = painter->sceneref;
	painter->lim[0] = 1.0f;
	painter->lim[1] = T_MAX;
	painter->lim[2] = R_LIMIT;
	painter->ray.o = scene->cam.t_m.p;
	painter->ray.d = throught_vp(cnv, scene->viewport);
	painter->ray.d = normalize_vec4(mat_apply(scene->cam.t_m, painter->ray.d));
}
// throw ray for every point of the canvas
void	display_color(t_painter *painter)
{
	t_data			*scene;
	t_vec2			pix;
	char			res;
	t_vec2			cnv;
	t_viewport		vp;
	t_argb			color;
	int				x;
	int				y;

	scene = painter->sceneref;
	//cnv = scene->cnv;
	vp = scene->viewport;
	res = scene->res;
	ft_bzero(&painter->ray, sizeof(t_ray));
	cnv.x = (-WIDTH / 2) + ((painter->id - 1) * (WIDTH / THREAD_NB));
	while (cnv.x < painter->id * (HEIGHT / THREAD_NB))
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
