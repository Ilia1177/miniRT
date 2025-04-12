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
void	display_coloriSAVE(t_data *scene)
{
	t_ray			ray;
	t_argb			color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;
	const char		res = scene->res;
	float			t_lim[2];

	ft_bzero(&ray, sizeof(t_ray));
	vp = scene->viewport;
	cnv = scene->cnv;
	t_lim[0] = 1.0f;
	t_lim[1] = T_MAX;
	cnv.loc.x = (-cnv.w / 2);
	while (cnv.loc.x < (cnv.w / 2))
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < (cnv.h / 2))
		{
			ray.o = scene->cam.t_m.p;
			ray.d = throught_vp(cnv, vp);
			ray.d = normalize_vec4(mat_apply(scene->cam.t_m, ray.d));
			color = throw_ray(&ray, t_lim, R_LIMIT, scene);
			pix = cnv_to_screen(cnv);
			color_screen(&scene->img, pix.x, pix.y, res, color);
			cnv.loc.y += res;
		}
		cnv.loc.x += res;
	}
}
//
// throw ray for every point of the canvas
void	display_color(t_data *scene, t_painter *painter)
{
	t_ray			ray; //[THREAD_NB];
	t_argb			color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;
	const char		res = scene->res;
	float			*lim;

	lim = painter->lim;
	ray = painter->ray;
	ft_bzero(&ray, sizeof(t_ray));
	vp = painter->vp;
	cnv = painter->cnv;
	lim[0] = 1.0f;
	lim[1] = T_MAX;
	lim[2] = R_LIMIT;

	cnv.loc.x = (-cnv.w / 2) + ((painter->id-1) * (cnv.w / THREAD_NB));
	while (cnv.loc.x < (painter->id) * (cnv.w / THREAD_NB) )
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < (cnv.h / 2))
		{
			ray.o = scene->cam.t_m.p;
			ray.d = throught_vp(cnv, vp);
			ray.d = normalize_vec4(mat_apply(scene->cam.t_m, ray.d));
			color = throw_ray(&ray, lim, R_LIMIT, scene);
			pix = cnv_to_screen(cnv);
			color_screen(&scene->img, pix.x, pix.y, res, color);
			cnv.loc.y += res;
		}
		cnv.loc.x += res;
	}
}
