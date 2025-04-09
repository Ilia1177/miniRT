#include <miniRT_bonus.h>
//
// get location of the point in the viemport from canvas'location
t_vec3 throught_vp(t_canvas cnv, t_viewport vp)
{
	t_vec3 dir;

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
		//	print_argb(color, "color argb:");
		//	printf("color :%x\n", encode_argb(color));
			rt_put_pixel(img, x + i, y + j, encode_argb(color));
		}
	}
}

// throw ray for every point of the canvas
void	display_color(t_data *scene)
{
	t_ray			ray;
	t_argb			color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;
	const char		res = scene->res;

	ray.o.w = 1;
	ray.d.w = 0;
	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = -cnv.w / 2;
	//update_camera_rotation(&scene->cam);
	while (cnv.loc.x < cnv.w / 2)
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < cnv.h / 2)
		{
			ray.o = scene->cam.t_m.p;
			ray.d = throught_vp(cnv, vp);
			ray.d = normalize_vec3(mat_apply(scene->cam.t_m, ray.d));
			color = throw_ray(&ray, 1.0f, T_MAX, R_LIMIT, scene);
			pix = cnv_to_screen(cnv);
			color_screen(&scene->img, pix.x, pix.y, res, color);
			cnv.loc.y += res;
		}
		cnv.loc.x += res;
	}
}

