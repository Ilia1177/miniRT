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

t_vec3 reflect_ray(t_vec3 dir, t_vec3 norm)
{
	t_vec3		reflection;
	const float	n_dot_d = dot_vec3(norm, dir);

//	if (n_dot_d < 0)
//	{
//		norm = mult_vec3(norm, -1);
//		reflection = mult_vec3(mult_vec3(norm, 2), n_dot_d * -1);
//	}
//	else
	reflection = mult_vec3(mult_vec3(norm, 2), n_dot_d);
	reflection = sub_vec3(reflection, dir);
	return (reflection);
}

t_argb	throw_ray(t_vec3 o, t_vec3 d, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	t_argb		reflected_color;
	t_argb		local_color;
	t_argb		luminosity;
	t_vec3		pt;
	t_vec3		n;
	t_vec3		reflected_ray;
	
	local_color = (t_argb) {0, 0, 0, 0};
	obj = closest_intersect(o, d, t_min, t_max, scene->objects);
	if (obj == NULL)
		return (local_color);
	pt = add_vec3(mult_vec3(d, obj->closest_t), o);

	if (obj->type == CYLINDER)
		n = cylinder_normal(pt, obj);
	else if (obj->type == SPHERE)
		n = sphere_normal(pt, o, d, obj);
	else
		n = plane_normal(d, obj->orientation);

	luminosity = compute_lighting(pt, n, mult_vec3(d, -1), obj->spec, scene);
	local_color = mult_colors(obj->color, luminosity);
	if (rec <= 0 || obj->reflect.a <= 0)
		return (local_color);
	reflected_ray = reflect_ray(mult_vec3(d, -1), n);
	reflected_color = throw_ray(pt, reflected_ray, 0.001f, t_max, rec - 1, scene);
	return (add_colors(mult_colors(local_color, ease_color(obj->reflect, 255)), mult_colors(reflected_color, obj->reflect)));
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
