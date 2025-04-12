#include <miniRT_bonus.h>

/*******************************************************************************
* Return reflexions of diffuse and/or specular
* d : direction from the point -> light
* v : vector from point -> camera
* n : normal of the surface, toward outside the shape
* n_dot_l > 0 --> light going against the normal (~ outside of the shape)
* n_dot_v > 0 --> camera is against the normal (~ outside of the shape)
*******************************************************************************/
t_argb	reflections(t_ray *ray, t_argb lumen, int spec)
{
	const float		n_dot_l = dot_vec3(ray->n, ray->d);
	const t_vec4	r = sub_vec4(mult_vec4(mult_vec4(ray->n, 2.0f), n_dot_l), ray->d);
	const float		r_dot_v = dot_vec3(r, ray->v);
	t_argb			diffuse;
	t_argb			specular;

	(void)spec;
	diffuse = (t_argb) {0, 0, 0, 0};
	specular = (t_argb) {0, 0, 0, 0};
	if (n_dot_l > 0)
	{
		diffuse = diffuse_reflect(ray, lumen, n_dot_l);
		if (spec != -1 && r_dot_v > 0)
			specular = specular_reflect(ray->v, r, r_dot_v, spec, lumen);
	}
	if (diffuse.a > 0 && specular.a > 0)
		return (add_colors(diffuse, specular));
	else if (diffuse.a > 0)
		return (diffuse);
	return (specular);
}

// More perpendicular the light is, more enlighten the point is.
//t_argb	diffuse_reflect(t_argb lumen, t_vec4 n, t_vec4 l, float n_dot_l)
t_argb	diffuse_reflect(t_ray *ray, t_argb lumen, float n_dot_l)
{
	const float	coeff = n_dot_l / (mag_vec4(ray->n) * mag_vec4(ray->d));
	t_argb	luminosity;

	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;
	luminosity.g = lumen.g * coeff;
	luminosity.b = lumen.b * coeff;
	limit_color(&luminosity);
	return (luminosity);
}

// Diffusion of the light on the surface.
// more the specular, better the shiny 
t_argb	specular_reflect(t_vec4 v, t_vec4 r, float r_dot_v, int spec, t_argb lumen)
{
	const float		coeff = powf(r_dot_v / (mag_vec4(r) * mag_vec4(v)), spec);
	t_argb			luminosity;

	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;	
	luminosity.g = lumen.g * coeff; 
	luminosity.b = lumen.b * coeff; 
	return (luminosity);
}

/*******************************************************************************
* Compute light coming at a point from all light sources
* 1) get the direction of the light form point to light (ray->o to light->pos)
* 2) if v_dot_n < 0 we are looking the inside the object, -> reverse normal
*******************************************************************************/
t_argb	compute_lighting(t_ray *ray, t_object *obj, t_data *scene)
{
	t_argb		lumen;
	t_light		*light;
	float		dist;

	(void)obj;
	lumen = (t_argb) {0, 0, 0, 0};
	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			lumen = add_colors(lumen, apply_brightness(light->intensity));
		else
		{
			if (light->type == POINT)
			{
				ray->d = normalize_vec4(sub_vec4(light->pos, ray->o));
				dist = dist_vec4(ray->o, light->pos);
			}
			else if (light->type == DIRECTIONAL)
			{
				ray->d = light->pos;
				dist = T_MAX;
			}
			if (!closest_intersect(ray, 1, 0.001f, dist, scene->objects))
				lumen = add_colors(reflections(ray, apply_brightness(light->intensity), obj->spec), lumen);
		}
		light = light->next;
	}
	return (lumen);
}
