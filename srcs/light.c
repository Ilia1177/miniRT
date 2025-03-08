#include <miniRT.h>

unsigned int darken_color(unsigned int color, float factor)
{
    unsigned int a = (color >> 24) & 0xFF;  // Extract Alpha
    unsigned int r = (color >> 16) & 0xFF;  // Extract Red
    unsigned int g = (color >> 8)  & 0xFF;  // Extract Green
    unsigned int b = (color)       & 0xFF;  // Extract Blue

    r = (unsigned int)(r * factor);
    g = (unsigned int)(g * factor);
    b = (unsigned int)(b * factor);
    return ((a << 24) | (r << 16) | (g << 8) | b);
}

float	compute_lighting(t_vec3 point, t_vec3 norm, t_vec3 v, int specular, t_data *scene)
{
	float 		intensity = 0.0;
	t_light		*light;
	t_vec3		l_dir;
	float		n_dot_l;
	float		r_dot_v;
	t_vec3		r;
	t_sphere	*shadow_s;

	light = scene->light;
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
			// Diffuse reflexion
			n_dot_l = dot_product(norm, l_dir);

		//	shadow_s = get_closest_sphere(point, l_dir, 0.001, INT_MAX, scene);
		//	if (shadow_s != NULL)
		//§		continue ;
			if (n_dot_l > 0)
				intensity += light->intensity * n_dot_l / (mag_vec3(norm) * mag_vec3(l_dir));
			// Specular reflexion
			if (specular != -1)
			{
				r = sub_vec3(mult_vec3(mult_vec3(norm, 2), dot_product(norm, l_dir)), l_dir);
				r_dot_v = dot_product(r, v);
				if (r_dot_v > 0)
					intensity += light->intensity * pow(r_dot_v / (mag_vec3(r) * mag_vec3(v)), specular);
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
