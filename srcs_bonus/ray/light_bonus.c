/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:54:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:43:22 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// More perpendicular the light is, more enlighten the point is.
//t_argb	diffuse_reflect(t_argb lumen, t_vec4 n, t_vec4 l, float n_dot_l)
static t_argb	diffuse_reflect(t_ray *ray, t_argb lumen, float n_dot_l)
{
	const float	coeff = n_dot_l / (mag_vec4(ray->n) * mag_vec4(ray->d));
	t_argb		luminosity;

	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;
	luminosity.g = lumen.g * coeff;
	luminosity.b = lumen.b * coeff;
	argb_clamp(&luminosity);
	return (luminosity);
}

// Diffusion of the light on the surface.
// more the specular, better the shiny 
// vector v =  inverse direction (hit point to camera)
static t_argb	specular_reflect(t_vec4 v, t_vec4 r, int spec, t_argb lumen)
{
	const float	r_dot_v = dot_vec3(r, v);
	float		coeff;
	t_argb		luminosity;

	if (r_dot_v <= 0)
		return ((t_argb){0, 0, 0, 0});
	coeff = powf(r_dot_v / (mag_vec4(r) * mag_vec4(v)), spec);
	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;
	luminosity.g = lumen.g * coeff;
	luminosity.b = lumen.b * coeff;
	argb_clamp(&luminosity);
	return (luminosity);
}

/*******************************************************************************
* Return reflexions of diffuse and/or specular
* d : direction from the point -> light
* v : vector from point -> camera
* n : normal of the surface, toward outside the shape
* n_dot_l > 0 --> light going against the normal (~ outside of the shape)
* n_dot_v > 0 --> camera is against the normal (~ outside of the shape)
*******************************************************************************/
static t_argb	reflections(t_ray *ray, t_argb lumen, int spec)
{
	const float		ndl = dot_vec3(ray->n, ray->d);
	const t_vec4	r = sub_vec4(mult_vec4(mult_vec4(ray->n, 2.0f), ndl),
			ray->d);
	t_argb			diffuse;
	t_argb			specular;

	diffuse = (t_argb){0, 0, 0, 0};
	specular = (t_argb){0, 0, 0, 0};
	if (ndl > 0)
	{
		diffuse = diffuse_reflect(ray, lumen, ndl);
		if (spec > 0)
			specular = specular_reflect(ray->v, r, spec, lumen);
	}
	if (diffuse.a > 0 && specular.a > 0)
		return (argb_add(diffuse, specular));
	else if (diffuse.a > 0)
		return (diffuse);
	return (specular);
}

static t_argb	cpt_lgt_reflec(t_painter *pntr, t_light *light, t_object *obj)
{
	float			*lim;
	t_ray			*ray;
	t_argb			lumen;
	const t_data	*scene = pntr->sceneref;

	ft_bzero(&lumen, sizeof(t_argb));
	lim = pntr->lim;
	ray = &pntr->ray;
	lim[0] = EPSILON;
	if (light->type == POINT)
	{
		ray->d = normalize_vec4(sub_vec4(light->pos, ray->o));
		lim[1] = dist_vec4(ray->o, light->pos);
	}
	else if (light->type == DIRECTIONAL)
	{
		ray->d = normalize_vec4(light->pos);
		lim[1] = T_MAX;
	}
	if (!closest_intersect(pntr, 1, scene->objects))
		lumen = reflections(ray, argb_applyalpha(light->intensity), obj->spec);
	return (lumen);
}

/*******************************************************************************
* Compute light coming at a point from all light sources
* 1) get the direction of the light form point to light (ray->o to light->pos)
* 2) if v_dot_n < 0 we are looking the inside the object, -> reverse normal
*******************************************************************************/
t_argb	compute_lighting(t_painter *painter, t_object *obj)
{
	t_argb		lumen;
	t_argb		reflection;
	t_light		*light;

	lumen = (t_argb){0, 0, 0, 0};
	light = painter->sceneref->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			lumen = argb_add(lumen, argb_applyalpha(light->intensity));
		else
		{
			reflection = cpt_lgt_reflec(painter, light, obj);
			lumen = argb_add(reflection, lumen);
		}
		light = light->next;
	}
	return (lumen);
}
