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

// get screen's pixel from canvas's point,
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
	unsigned int	color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;

	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = -cnv.w / 2;
	//mouse_move(&scene->cam, 0.0f, -0.0f);
	while (cnv.loc.x < cnv.w / 2)
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < cnv.h / 2)
		{
			vp.loc = get_viewport_loc(cnv, vp);
			color = throw_ray(scene->cam.pos, vp.loc, 1, FLT_MAX, 8, scene);
		//	if (color != 0)
		//		printf("display_color: %X, pix.x: %d, pix.y: %d\n", color, (int)pix.x, (int)pix.y);
			pix = cnv_to_screen(cnv);
			rt_put_pixel(&scene->img, pix, color);
			cnv.loc.y++;
		}
		cnv.loc.x++;
	}
}
