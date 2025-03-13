#include <miniRT.h>

t_vec3 reflect_ray(t_vec3 ray, t_vec3 norm)
{
	t_vec3 reflection;

	reflection = mult_vec3(mult_vec3(norm, 2), dot_vec3(norm, ray));
	reflection = sub_vec3(reflection, ray);
	return (reflection);
}

unsigned int add_colors(unsigned int c1, unsigned int c2)
{
    unsigned int a = ((c1 >> 24) & 0xFF) + ((c2 >> 24) & 0xFF);
    unsigned int r = ((c1 >> 16) & 0xFF) + ((c2 >> 16) & 0xFF);
    unsigned int g = ((c1 >> 8)  & 0xFF) + ((c2 >> 8)  & 0xFF);
    unsigned int b = (c1 & 0xFF) + (c2 & 0xFF);

    /* if (a > 255) */
		/* a = 255; */
    /* if (r > 255) */
		/* r = 255; */
    /* if (g > 255) */
		/* g = 255; */
    /* if (b > 255) */
		/* b = 255; */
    return (a << 24) | (r << 16) | (g << 8) | b;
}

unsigned int mult_colors(unsigned int color, float factor)
{
    unsigned int a = (color >> 24) & 0xFF;  // Extract Alpha
    unsigned int r = (color >> 16) & 0xFF;  // Extract Red
    unsigned int g = (color >> 8)  & 0xFF;  // Extract Green
    unsigned int b = (color)       & 0xFF;  // Extract Blue

    r = (unsigned int)(r * factor);
    g = (unsigned int)(g * factor);
    b = (unsigned int)(b * factor);
    /* if (a > 255) */
		/* a = 255; */
    /* if (r > 255) */
		/* r = 255; */
    /* if (g > 255) */
		/* g = 255; */
    /* if (b > 255) */
		/* b = 255; */
    return ((a << 24) | (r << 16) | (g << 8) | b);
}

// compute light at a point from all light sources
float	compute_lighting(t_vec3 point, t_vec3 norm, t_vec3 v, int specular, t_data *scene)
{
	float 		intensity = 0.0;
	t_light		*light;
	t_vec3		l_dir;
	float		n_dot_l;
	float		r_dot_v;
	t_vec3		r;
	t_object	*obs;

	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			intensity += light->intensity;
		else
		{
			if (light->type == POINT)
				l_dir = sub_vec3(light->pos, point);
			else if (light->type == DIRECTIONAL)
				l_dir = light->dir;

			obs = closest_intersect(point, l_dir, 0.001, FLT_MAX, scene->objects);
			if (!obs)
			{
				// Diffuse reflexion
				n_dot_l = dot_vec3(norm, l_dir);
				if (n_dot_l > 0)
					intensity += light->intensity * n_dot_l / (mag_vec3(norm) * mag_vec3(l_dir));
				// Specular reflexion
				if (specular != -1)
				{
					r = sub_vec3(mult_vec3(mult_vec3(norm, 2), dot_vec3(norm, l_dir)), l_dir);
					r_dot_v = dot_vec3(r, v);
					if (r_dot_v > 0)
						intensity += light->intensity * pow(r_dot_v / (mag_vec3(r) * mag_vec3(v)), specular);
				}
			}
		}
		light = light->next;
	}
	if (intensity > 1)
		intensity = 1;
	else if (intensity < 0)
		intensity = 0;
	return (intensity);
}
