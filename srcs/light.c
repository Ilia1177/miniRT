#include <miniRT.h>

// Return reflexions of diffuse and/or specular
// d : direction from the point -> light
// v : vector from point -> camera
// n : normal of the surface, toward outside the shape
// n_dot_l > 0 --> light going against the normal (~ outside of the shape)
// n_dot_v > 0 --> camera is against the normal (~ outside of the shape)
t_argb	reflections(t_vec3 l, t_vec3 v, t_vec3 n, t_argb lumen, int spec)
{
	const float		n_dot_l = dot_vec3(n, l);
	const t_vec3	r = sub_vec3(mult_vec3(mult_vec3(n, 2.0f), n_dot_l), l);
	const float		r_dot_v = dot_vec3(r, v);
	t_argb			diffuse;
	t_argb			specular;

	diffuse = (t_argb) {0, 0, 0, 0};
	specular = (t_argb) {0, 0, 0, 0};
	if (n_dot_l > 0) //&& (dot_vec3(n, v) < 0 && dot_vec3(l, v) > 0))
		diffuse = diffuse_reflect(lumen, n, l, n_dot_l);
	if (spec != -1 && r_dot_v > 0)
		specular = specular_reflect(v, r, r_dot_v, spec, lumen);
	if (diffuse.a > 0 && specular.a > 0)
		return (add_colors(diffuse, specular));
	else if (diffuse.a > 0)
		return (diffuse);
	return (specular);
}

// More perpendicular the light is, more enlighten the point is.
t_argb	diffuse_reflect(t_argb lumen, t_vec3 n, t_vec3 l, float n_dot_l)
{
	const float	coeff = n_dot_l / (mag_vec3(n) * mag_vec3(l));
	t_argb	luminosity;

	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;
	luminosity.g = lumen.g * coeff;
	luminosity.b = lumen.b * coeff;
	return (luminosity);
}

// Diffusion of the light on the surface.
// more the specular, better the shiny 
t_argb	specular_reflect(t_vec3 v, t_vec3 r, float r_dot_v, int spec, t_argb lumen)
{
	const float		coeff = pow(r_dot_v / (mag_vec3(r) * mag_vec3(v)), spec);
	t_argb			luminosity;

	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;	
	luminosity.g = lumen.g * coeff; 
	luminosity.b = lumen.b * coeff; 
	return (luminosity);
}

// Compute light at a point from all light sources
// v  =	vector to camera (ray direction * -1), used to compute specular_reflection
// n  =	normal of the surface where the point hit
// pt = point ont the surface where to compute light
t_argb	compute_lighting(t_object *obj, t_vec3 pt, t_vec3 n, t_vec3 v, int spec, t_data *scene)
{
	t_argb		lumen;
	t_light		*light;
	t_vec3		dir;
	float		dist;
	t_object	*shadow;

	(void)obj;
	lumen = (t_argb) {0, 0, 0, 0};
	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			lumen = add_colors(lumen, light->intensity);
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
			shadow = closest_intersect(pt, dir, 0.001f, dist, scene->objects);
			if (!shadow) //&& dot_vec3(v, mult_vec3(dir, -1)) < 0)
				lumen = add_colors(reflections(dir, v, n, light->intensity, spec), lumen);
		}
		light = light->next;
	}
	return (lumen);
}
