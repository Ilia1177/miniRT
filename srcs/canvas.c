#include <miniRT.h>
//
// get location of the point in the viemport from canvas'location
t_vec3 get_viewport_loc(t_canvas cnv, t_viewport vp)
{
	t_vec3 vp_loc;

	vp_loc.x = cnv.loc.x * vp.w / cnv.w;
	vp_loc.y = cnv.loc.y * vp.h / cnv.h;
	vp_loc.z = 1;
	return (vp_loc);
}

// get screen's pixel from canvas's point
t_vec2 cnv_to_screen(t_canvas cnv)
{
	t_vec2 screen;

	screen.x = (cnv.w / 2) + cnv.loc.x;
	screen.y = (cnv.h / 2) - cnv.loc.y;
	return (screen);
}

void	print_vec3(t_vec3 v, char *msg)
{
	printf("%s{x: %f, y: %f, z:%f}\n", msg, v.x, v.y, v.z );
}

// throw ray for every point of the canvas
void	display_color(t_data *scene)
{
	t_argb			color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;

	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = -cnv.w / 2;
	update_camera_vectors(&scene->cam);
	while (cnv.loc.x < cnv.w / 2)
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < cnv.h / 2)
		{
			vp.loc = get_viewport_loc(cnv, vp);
			vp.loc = apply_camera_rotation(scene->cam, vp.loc);
			color = throw_ray(scene->cam.pos, vp.loc, 1, FLT_MAX, 8, scene);
			pix = cnv_to_screen(cnv);
			rt_put_pixel(&scene->img, pix, encode_argb(color));
			cnv.loc.y++;
		}
		cnv.loc.x++;
	}
}
