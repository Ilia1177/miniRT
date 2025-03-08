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
	unsigned int	color;
	t_viewport		vp;
	t_canvas		cnv;
	t_vec2			pix;

	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = -cnv.w / 2;
	while (cnv.loc.x < cnv.w / 2)
	{
		cnv.loc.y = -cnv.h / 2;
		while (cnv.loc.y < cnv.h / 2)
		{
			vp.loc = get_viewport_loc(cnv, vp);
			color = throw_ray(vp.loc, 1, INT_MAX, scene);
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

t_sphere *get_closest_sphere(t_vec3 origin, t_vec3 dir, int t_min, int t_max, t_data *scene)
{
	t_sphere	*closest_sphere;
	t_sphere	*curr_sphere;
	float		closest_t;
	float		*solution;

	closest_t = INT_MAX;
	closest_sphere	= NULL;
	curr_sphere = scene->sphere;
	while (curr_sphere)
	{
		solution = curr_sphere->intersection;
		intersect_sphere(origin, dir, curr_sphere, scene);
		if (solution[0] >= t_min && solution[0] <= t_max)
		{
			if (solution[0] < closest_t)
			{
				curr_sphere->closest_t = solution[0];
				closest_sphere = curr_sphere;
			}
		}
		if (solution[1] >= t_min && solution[1] <= t_max)
		{
			if (solution[1] < closest_t)
			{
				curr_sphere->closest_t = solution[1];
				closest_sphere = curr_sphere;
			}
		}
		curr_sphere = curr_sphere->next;
	}
	return (closest_sphere);
}

int	throw_ray(t_vec3 dir, int t_min, int t_max, t_data *scene)
{
	t_sphere	*sphere;
	int			color;
	float		luminosity;
	t_vec3		point;
	t_vec3		normal;

	sphere = get_closest_sphere(scene->cam, dir, t_min, t_max, scene);
	if (sphere == NULL)
		return (0x00000000);
	point = add_vec3(mult_vec3(dir, sphere->closest_t), scene->cam);
	normal = sub_vec3(point, sphere->pos);	
	normal = normalize_vec3(normal);
	luminosity = compute_lighting(point, normal, mult_vec3(dir, -1), sphere->specular, scene);
	color = darken_color(sphere->color, luminosity);
	return (color);
}

int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_sphere *sphere, t_data *scene)
{
	float	r = sphere->radius;
	float	a, b, c;
	float	discriminant;
	t_vec3	substract;

	substract = sub_vec3(origin, sphere->pos);
	a = dot_product(dir, dir);
	b = 2 * dot_product(substract, dir);
	c = dot_product(substract, substract) - r * r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		sphere->intersection[0] = INT_MAX;
		sphere->intersection[1] = INT_MAX;
		return (0);
	}
	sphere->intersection[0] = (-b + sqrt(discriminant)) / (2 * a);
	sphere->intersection[1] = (-b - sqrt(discriminant)) / (2 * a);
	return (1);
}

int	IntersectRaySphere(t_vec3 dir, t_sphere sphere, t_data *scene)
{
	float	r = sphere.radius;
	float	a, b, c;
	float	discriminant;
	t_vec3	substract;

	substract = sub_vec3(scene->cam, sphere.pos);
	a = dot_product(dir, dir);
	b = 2 * dot_product(substract, dir);
	c = dot_product(substract, substract) - r * r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		scene->intersec_p[0] = INT_MAX;
		scene->intersec_p[1] = INT_MAX;
		return (0);
	}
	scene->intersec_p[0] = (-b + sqrt(discriminant)) / (2 * a);
	scene->intersec_p[1] = (-b - sqrt(discriminant)) / (2 * a);
	return (1);
}
