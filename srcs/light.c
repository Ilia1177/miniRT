#include <miniRT.h>

t_vec3 reflect_ray(t_vec3 dir, t_vec3 norm)
{
	t_vec3 reflection;
	
	reflection = mult_vec3(mult_vec3(norm, 2), dot_vec3(norm, dir));
	reflection = sub_vec3(reflection, dir);
	return (reflection);
}

t_argb	diffuse_reflex(t_argb intensity, t_vec3 norm, t_vec3 l_dir)
{
	float	n_dot_l = dot_vec3(norm, l_dir);
	float	coeff;
	t_argb	luminosity;

	luminosity = (t_argb) {0, 0, 0, 0};
	if (n_dot_l > 0)
	{
		coeff = n_dot_l / (mag_vec3(norm) * mag_vec3(l_dir));
		luminosity.a = intensity.a * coeff;
		luminosity.r = intensity.r * coeff;
		luminosity.g = intensity.g * coeff;
		luminosity.b = intensity.b * coeff;
	}
	return (luminosity);
}

t_argb	specular_reflex(t_argb intensity, t_vec3 v, t_vec3 norm, t_vec3 l_dir, int specular)
{
	const t_vec3	r = sub_vec3(mult_vec3(mult_vec3(norm, 2.0f), dot_vec3(norm, l_dir)), l_dir);
	const float		r_dot_v = dot_vec3(r, v);
	float			coeff;
	t_argb			luminosity;

	luminosity = (t_argb) {0, 0, 0, 0};
	if (r_dot_v > 0)
	{
		coeff = pow(r_dot_v / (mag_vec3(r) * mag_vec3(v)), specular);
		luminosity.a = intensity.a * coeff;
		luminosity.r = intensity.r * coeff;	
		luminosity.g = intensity.g * coeff; 
		luminosity.b = intensity.b * coeff; 
	}
	return (luminosity);
}

// compute light at a point from all light sources
t_argb	compute_lighting(t_vec3 pt, t_vec3 norm, t_vec3 v, int specular, t_data *scene)
{
	t_argb		intensity;
	t_light		*light;
	t_vec3		l_dir;
	float		dist;

	intensity = (t_argb) {0, 0, 0, 0};
	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			intensity = add_colors(intensity, light->intensity);
		else
		{
			if (light->type == POINT)
			{
				l_dir = normalize_vec3(sub_vec3(light->pos, pt));
				dist = dist_vec3(pt, light->pos);
			}
			else if (light->type == DIRECTIONAL)
			{
				l_dir = light->dir;
				dist = FLT_MAX;
			}
			if (!closest_intersect(pt, l_dir, 0.001f, dist, scene->objects))
			{
				norm  = normalize_vec3(norm);
				intensity = add_colors(diffuse_reflex(light->intensity, norm, l_dir), intensity);
				if (specular != -1)
					intensity = add_colors(specular_reflex(light->intensity, v, norm, l_dir, specular), intensity);
			}
		}
		light = light->next;
	}
	return (intensity);
}
