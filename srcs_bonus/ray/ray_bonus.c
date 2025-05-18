/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:00:39 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 13:01:27 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	ray_reflect(t_ray *ray)
{
	const float	n_dot_d = dot_vec3(ray->n, ray->v);

	ray->d = mult_vec4(mult_vec4(ray->n, 2.0f), n_dot_d);
	ray->d = normalize_vec4(sub_vec4(ray->n, ray->v));
}

void	ray_reflect2(t_ray *ray)
{
	const float n_dot_v = dot_vec3(ray->n, ray->v);
	t_vec4 scaled_normal = mult_vec4(ray->n, 2.0f * n_dot_v);
	ray->d = normalize_vec4(sub_vec4(ray->v, scaled_normal));
}

void	normal_map(t_ray *ray, t_object *obj)
{
	const t_mat4	orthogonal = mat_orthogonal(ray->n);
	const t_mat4	inv = mat_inverse(obj->t_m);
	const t_uv		uv = get_uv(obj, mat_apply(inv, ray->o));
	const t_argb	color = img_at(uv.u, uv.v, obj->img);;
	t_vec4			normal;

	normal.x = (color.r / 255.0f)* 2.0f - 1.0f;
	normal.y = (color.g / 255.0f)* 2.0f - 1.0f;
	normal.z = (color.b / 255.0f)* 2.0f - 1.0f;
	normal.w = 0.0f;
	normal = mat_apply(orthogonal, normalize_vec4(normal));
	ray->n = normalize_vec4(normal);
}

// 1. Compute new origin of ray = hit point in world space
// 2. Get the vector to camera
// 3. Compute normal of object
static void	ray_hitpoint(t_painter *painter, t_object *obj)
{
	t_ray	*ray;

	ray = &painter->ray;
	ray->o = add_vec4(mult_vec4(ray->d, painter->t), ray->o);
	ray->v = mult_vec4(ray->d, -1.0f);
	if (obj->type == CYLINDER)
		cylinder_normal(ray, obj);
	else if (obj->type == SPHERE)
		sphere_normal(ray, obj);
	else if (obj->type == PLANE)
		plane_normal(ray, obj);
	else if (obj->type == TRIANGLE)
		triangle_normal(ray, obj);
	else
		hyperboloid_normal(ray, obj);
	if (dot_vec3(ray->n, ray->v) < EPSILON)
		ray->n = mult_vec4(ray->n, -1);
	if (obj->normal_map)
		normal_map(ray, obj);
}

static t_argb	get_reflected_color(t_painter *painter)
{
	t_argb	reflected_color;

	ft_bzero(&reflected_color, sizeof(reflected_color));
	//ray_reflect(&painter->ray);
	painter->lim[0] = EPSILON;
	painter->lim[2] -= 1.0f;
	reflected_color = throw_ray(painter);
	return (reflected_color);
}

/*******************************************************************************
* 1) find intersection between ray and object
* 1.2. Compute t (distance on the rat->d);
* 2) get the hitting point, and assign it to ray->origin
* 3) calcul the normal of the hitting point in ray->n
* 4) compute light at hitting point
* 5) return color if no reflective or recursive <= 0
* 6) reflect ray and throw new ray to get reflections
*******************************************************************************/
//t_argbthrow_ray(t_ray *ray, float t_min, float t_max, int rec, t_data *scene)
t_argb	throw_ray(t_painter *painter)
{
	t_object	*obj;
	t_data		*scene;
	t_argb		local_color;
	t_argb		reflected_color;
	t_argb		lumen;

	scene = painter->sceneref;
	ft_bzero(&local_color, sizeof(t_argb));
	obj = closest_intersect(painter, 0, scene->objects);
	if (obj == NULL)
		return (local_color);
	ray_hitpoint(painter, obj);
	lumen = compute_lighting(painter, obj);
	local_color = argb_mult(mapping(&painter->ray, obj), lumen);
	if (painter->lim[2] <= 0.0f || obj->reflect.a <= 0)
		return (local_color);

	//	reflect ray
	t_ray *ray = &painter->ray;

	t_vec4 normal = normalize_vec4(ray->n);  // Ensure normal is unit length
	t_vec4 view = normalize_vec4(ray->v);    // Ensure incoming vector is unit length

	float n_dot_v = dot_vec4(normal, view);

	t_vec4 scaled_normal = mult_vec4(normal, 2.0f * n_dot_v);
	ray->d = normalize_vec4(sub_vec4(view, scaled_normal));  // reflected = view - 2*(n.v)*n


	//t_vec4 normal = ray->n;
	//const float	n_dot_d = dot_vec4(normal, ray->v);

	//ray->d = mult_vec4(mult_vec4(normal, 2.0f), n_dot_d);
	//ray->d = normalize_vec4(sub_vec4(ray->d, ray->v));


	reflected_color = get_reflected_color(painter);
	local_color = argb_mult(local_color, argb_ease(obj->reflect, 255));
	reflected_color = argb_mult(reflected_color, obj->reflect);
	return (argb_add(local_color, reflected_color));
}
