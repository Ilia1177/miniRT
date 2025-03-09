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

		//	vp.loc.x *= scene->cam_rotation.x;
		//	vp.loc.y *= scene->cam_rotation.y;
		//	vp.loc.z *= scene->cam_rotation.z;



			color = throw_ray(scene->cam, vp.loc, 1, INT_MAX, 2, scene);
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

//	float	closest_intersection(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_data *scene)
//	{
//
//	}

t_sphere *get_closest_sphere(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_data *scene)
{
	t_sphere	*closest_sphere;
	t_sphere	*curr_sphere;
	float		closest_t;
	float		*solution;

	closest_t = FLT_MAX;
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

int	throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene)
{
	t_sphere	*sphere;
	int			reflected_color;
	int			local_color;
	float		luminosity;
	t_vec3		point;
	t_vec3		normal;
	int			reflective;
	t_vec3		reflected_ray;

	sphere = get_closest_sphere(origin, dir, t_min, t_max, scene);
	if (sphere == NULL)
		return (0x00000000);
	point = add_vec3(mult_vec3(dir, sphere->closest_t), scene->cam);
	normal = sub_vec3(point, sphere->pos);	
	normal = normalize_vec3(normal);
	luminosity = compute_lighting(point, normal, mult_vec3(dir, -1), sphere->specular, scene);
	local_color = mult_colors(sphere->color, luminosity);

	if (rec <= 0 || sphere->reflective <= 0)
		return (local_color);

	reflected_ray = reflect_ray(mult_vec3(dir, -1), normal);
	reflected_color = throw_ray(point, reflected_ray, 0.001, FLT_MAX, rec - 1, scene);

	return (add_colors(mult_colors(local_color, 1 - sphere->reflective), mult_colors(reflected_color, sphere->reflective)));
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
		sphere->intersection[0] = FLT_MAX;
		sphere->intersection[1] = FLT_MAX;
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
