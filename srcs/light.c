/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:12:27 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/29 19:54:06 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

// Return reflexions of diffuse and/or specular
// d : direction from the point -> light
// v : vector from point -> camera
// n : normal of the surface, toward outside the shape
// n_dot_l > 0 --> light going against the normal (~ outside of the shape)
// n_dot_v > 0 --> camera is against the normal (~ outside of the shape)
t_argb	reflections(t_ray *ray, t_argb lumen)
{
	const float		n_dot_l = dot_vec4(ray->n, ray->d);
   // const t_vec4	r = sub_vec4(mult_vec4(mult_vec4(ray->n, 2.0f), n_dot_l),
   // 		ray->d);
	//const float		r_dot_v = dot_vec4(r, ray->v);
	t_argb			diffuse;
	t_argb			specular;
	
	diffuse = (t_argb){0, 0, 0, 0};
	specular = (t_argb){0, 0, 0, 0};
	if (n_dot_l > 0)
	{
		diffuse = diffuse_reflect(ray, lumen, n_dot_l);
	   // if (spec != -1 && r_dot_v > 0)
	   // 	specular = specular_reflect(ray->v, r, r_dot_v, spec, lumen);
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
	t_argb		luminosity;

	luminosity.a = lumen.a * coeff;
	luminosity.r = lumen.r * coeff;
	luminosity.g = lumen.g * coeff;
	luminosity.b = lumen.b * coeff;
	limit_color(&luminosity);
	return (luminosity);
}

// Diffusion of the light on the surface.
// more the specular, better the shiny 
//t_argbspecular_reflect(t_vec4 v, t_vec4 r, float r_d_v, int spec, t_argb lum)
//{
//	const float		coeff = pow(r_d_v / (mag_vec4(r) * mag_vec4(v)), spec);
//	t_argb			luminosity;
//
//	luminosity.a = lum.a * coeff;
//	luminosity.r = lum.r * coeff;
//	luminosity.g = lum.g * coeff;
//	luminosity.b = lum.b * coeff;
//	return (luminosity);
//}

void	add_type_light(t_light *light, t_argb *lumen, t_painter painter)
{
	if (light->type == AMBIENT)
		*lumen = add_colors(*lumen, apply_brightness(light->intensity));
	else
	{
		if (light->type == POINT)
		{
			painter.ray.d = normalize_vec4(sub_vec4(light->pos, painter.ray.o));
			painter.tmax = dist_vec4(painter.ray.o, light->pos);
		}
		else if (light->type == DIRECTIONAL)
			painter.ray.d = light->dir;
		if (!closest_intersect(&painter, 1, painter.scene->objects))
			*lumen = add_colors(reflections(&painter.ray,
						apply_brightness(light->intensity)), *lumen);
	}
}

// Compute light coming at a point from all light sources
// 1) get the direction of the light form point to light (ray->o to light->pos)
// 2) if v_dot_n < 0 we are looking the inside the object, -> reverse n
// 3) 
t_argb	compute_lighting(t_ray *ray, t_data *scene)
{
	t_argb			lumen;
	t_light			*light;
	t_painter		painter;

	lumen = (t_argb){0, 0, 0, 0};
	light = scene->lights;
	init_painter(&painter, scene, ray);
	while (light)
	{
		add_type_light(light, &lumen, painter);
		light = light->next;
	}
	return (lumen);
}
