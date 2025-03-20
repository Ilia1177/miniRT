/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:32:49 by npolack           #+#    #+#             */
/*   Updated: 2025/03/14 17:01:52 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	reflect_ray(t_ray *ray)
{
	const float	n_dot_d = dot_vec3(ray->n, ray->v);

//	if (n_dot_d < 0)
//	{
//		norm = mult_vec3(norm, -1);
//		reflection = mult_vec3(mult_vec3(norm, 2), n_dot_d * -1);
//	}
//	else
	ray->d = mult_vec3(mult_vec3(ray->n, 2), n_dot_d);
	ray->d = sub_vec3(ray->d, ray->v);
}

//t_argb	throw_ray(t_vec3 o, t_vec3 d, float t_min, float t_max, int rec, t_data *scene)
t_argb	throw_ray(t_ray *ray, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	t_argb		reflected_color;
	t_argb		local_color;
	t_argb		lumen;
	t_vec3		pt;
	t_vec3		n;
	t_vec3		reflected_ray;
	
	local_color = (t_argb) {255, 0, 0, 0};
	obj = closest_intersect(ray, 0, t_min, t_max, scene->objects);
	if (obj == NULL)
		return (local_color);
	obj->pt = add_vec3(mult_vec3(ray->d, obj->t), ray->o);
	ray->v = mult_vec3(ray->d, -1);
	ray->o = obj->pt;
	if (obj->type == CYLINDER)
		cylinder_normal(ray, obj);
	else if (obj->type == SPHERE)
		sphere_normal(ray, obj);
	else
		plane_normal(ray, obj);
	lumen = compute_lighting(ray, obj, scene);
	local_color = mult_colors(obj->color, lumen);
	if (rec <= 0 || obj->reflect.a <= 0)
		return (local_color);
	reflect_ray(ray);
	reflected_color = throw_ray(ray, 0.001f, t_max, rec - 1, scene);
	local_color = mult_colors(local_color, ease_color(obj->reflect, 255));
	reflected_color = mult_colors(reflected_color, obj->reflect);
	return (add_colors(local_color, reflected_color));
}

t_quad	solve_quadratic(t_vec3 oc, t_vec3 dir, float radius)
{
	t_quad	quad;
	float	square_root;

	quad.a = dot_vec3(dir, dir);
	quad.b = 2.0f * dot_vec3(oc, dir);
	quad.c = dot_vec3(oc, oc) - radius * radius;
	quad.delta = quad.b * quad.b - 4.0f * quad.a * quad.c;
	if (quad.delta < 0)
	{
		quad.t[0] = FLT_MAX;
		quad.t[1] = FLT_MAX;
		return (quad);
	}
	square_root = sqrtf(quad.delta);
	quad.t[0] = (-quad.b - square_root) / (2.0f * quad.a);
	quad.t[1] = (-quad.b + square_root) / (2.0f * quad.a);
	return (quad);
}
