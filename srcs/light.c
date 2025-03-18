#include <miniRT.h>

// Return reflexions of diffuse and/or specular
// d : direction from the point -> light
// v : vector from point -> camera
// n : normal of the surface
t_argb	reflections(t_vec3 d, t_vec3 v, t_vec3 n, t_argb intensity, int spec)
{
	const float		n_dot_d = dot_vec3(n, d);
	const t_vec3	r = sub_vec3(mult_vec3(mult_vec3(n, 2.0f), n_dot_d), d);
	const float		r_dot_v = dot_vec3(r, v);
	t_argb			diffuse;
	t_argb			specular;

	diffuse = (t_argb) {0, 0, 0, 0};
	specular = (t_argb) {0, 0, 0, 0};
	if (n_dot_d > 0)
		diffuse = diffuse_reflect(intensity, n, d, n_dot_d);
	if (spec != -1 && r_dot_v > 0)
		specular = specular_reflect(v, r, r_dot_v, spec, intensity);
	if (diffuse.a > 0 && specular.a > 0)
		return (add_colors(diffuse, specular));
	else if (diffuse.a > 0)
		return (diffuse);
	return (specular);
}

// More perpendicular the light is, more enlighten the point is.
t_argb	diffuse_reflect(t_argb intensity, t_vec3 n, t_vec3 d, float n_dot_d)
{
	const float	coeff = n_dot_d / (mag_vec3(n) * mag_vec3(d));
	t_argb	luminosity;

	luminosity.a = intensity.a * coeff;
	luminosity.r = intensity.r * coeff;
	luminosity.g = intensity.g * coeff;
	luminosity.b = intensity.b * coeff;
	return (luminosity);
}

// Diffusion of the light on the surface.
// more the specular, better the shiny 
t_argb	specular_reflect(t_vec3 v, t_vec3 r, float r_dot_v, int spec, t_argb intens)
{
	const float		coeff = pow(r_dot_v / (mag_vec3(r) * mag_vec3(v)), spec);
	t_argb			luminosity;

	luminosity.a = intens.a * coeff;
	luminosity.r = intens.r * coeff;	
	luminosity.g = intens.g * coeff; 
	luminosity.b = intens.b * coeff; 
	return (luminosity);
}

// Compute light at a point from all light sources
// v  =	vector to camera (ray direction * -1), used to compute specular_reflection
// n  =	normal of the surface where the point hit
// pt = point ont the surface where to compute light
t_argb	compute_lighting(t_vec3 pt, t_vec3 n, t_vec3 v, int spec, t_data *scene)
{
	t_argb		intensity;
	t_light		*light;
	t_vec3		dir;
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
				dir = normalize_vec3(sub_vec3(light->pos, pt));
				dist = dist_vec3(pt, light->pos);
			}
			else if (light->type == DIRECTIONAL)
			{
				dir = light->dir;
				dist = T_MAX;
			}
			if (!closest_intersect(pt, dir, 0.001f, dist, scene->objects))
				intensity = add_colors(reflections(dir, v, n, light->intensity, spec), intensity);
		}
		light = light->next;
	}
	return (intensity);
}
