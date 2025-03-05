#include <miniRT.h>
#include <math.h>

// get screen's pixel from canvas's point,
t_vec2 cnv_to_screen(t_canvas cnv)
{
	t_vec2 screen;

	screen.x = (cnv.w / 2) + cnv.loc.x;
	screen.y = (cnv.h / 2) - cnv.loc.y;
	return (screen);
}

// throw ray for every point of the canvas
void	display_color(t_data *scene)
{
	int			color;
	t_viewport	vp;
	t_canvas	cnv;
	t_vec2		pix;

	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = -cnv.w / 2;
	while (cnv.loc.x < cnv.w / 2)
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < cnv.h / 2)
		{
			vp.loc = get_viewport_loc(cnv, vp);
			color = throw_ray(scene->cam, vp.loc, 1, INT_MAX, scene);
			pix = cnv_to_screen(cnv);
			rt_put_pixel(&scene->img, pix, color);
			cnv.loc.y++;
		}
		cnv.loc.x++;
	}
}

// get location of the point in the viemport from canvas'location
t_vec3 get_viewport_loc(t_canvas cnv, t_viewport vp)
{
	t_vec3 vp_loc;

	vp_loc.x = cnv.loc.x * vp.w / cnv.w;
	vp_loc.y = cnv.loc.y * vp.h / cnv.h;
	vp_loc.z = vp.pos.z;
	return (vp_loc);
}

int	throw_ray(t_vec3 cam, t_vec3 dir, int t_min, int t_max, t_data *scene)
{
	t_sphere	*closest_sphere;
	t_sphere	*curr_sphere;
	float		closest_t;
	float		*solution;

	closest_t = INT_MAX;
	closest_sphere = NULL;
	curr_sphere = scene->sphere;
	while (curr_sphere)
	{
		solution = IntersectRaySphere(cam, dir, *curr_sphere);
		if (solution[0] >= t_min && solution[0] <= t_max)
		{
			if (solution[0] < closest_t)
			{
				closest_t = solution[0];
				closest_sphere = curr_sphere;
			}
		}
		if (solution[1] >= t_min && solution[1] <= t_max)
		{
			if (solution[1] < closest_t)
			{
				closest_t = solution[1];
				closest_sphere = curr_sphere;
			}
		}
		curr_sphere = curr_sphere->next;
		free(solution);
	}
	if (closest_sphere == NULL)
		return (0x00000000);
	return (closest_sphere->color);
}

float *IntersectRaySphere(t_vec3 cam, t_vec3 dir, t_sphere sphere)
{
	float	*result;
	float	r = sphere.radius;
	float	a, b, c;
	float	discriminant;
	t_vec3	substract;

	result = malloc(sizeof(float) * 2);
	substract = sub_vec3(cam, sphere.pos);
	a = dot_product(dir, dir);
	b = 2 * dot_product(substract, dir);
	c = dot_product(substract, substract) - r * r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		result[0] = INT_MAX;
		result[1] = INT_MAX;
		return (result);
	}
	result[0] = (-b + sqrt(discriminant)) / (2 * a);
	result[1] = (-b - sqrt(discriminant)) / (2 * a);
	return (result);
}
