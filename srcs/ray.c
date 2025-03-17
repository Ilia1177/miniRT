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
t_vec3	plane_normal(t_vec3 l_dir, t_vec3 norm)
{
	t_vec3 normal;

	if (dot_vec3(norm, l_dir) > 0.0f)
		normal = mult_vec3(norm, -1.0f);
	else
		normal = norm;
	return (normal);
}

t_vec3	sphere_normal(t_vec3 pt, t_vec3 origin, t_object *sphere, t_vec3 l_dir)
{
	t_vec3	normal;

	normal = normalize_vec3(sub_vec3(pt, sphere->pos));
//	if (dot_vec3(normal, l_dir) > 0)
//		normal = mult_vec3(normal, -1);
//t_vec3 compute_sphere_normal(t_vec3 hit_point, t_object *sphere)
    // If the ray originated inside the sphere, flip the normal
//    if (dot_vec3(normal, l_dir) > 0.0f)
  //      normal = mult_vec3(normal, -1.0f);
    float dist = dist_vec3(origin, sphere->pos);
    if (dist < sphere->radius)
	{
		printf("is inside\n");
        normal = mult_vec3(normal, -1.0f);
	}

	return (normal);
}

t_argb	throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	t_argb		reflected_color;
	t_argb		local_color;
	t_argb		luminosity;
	t_vec3		pt;
	t_vec3		normal;
	t_vec3		reflected_ray;
	
	local_color = (t_argb) {0, 0, 0, 0};
	obj = closest_intersect(origin, dir, t_min, t_max, scene->objects);
	if (obj == NULL)
		return (local_color);
	pt = add_vec3(mult_vec3(dir, obj->closest_t), scene->cam.pos);

	if (obj->type == CYLINDER)
		normal = cylinder_normal(pt, obj);
	else if (obj->type == SPHERE)
		normal = sphere_normal(pt, origin, obj, dir);
	else
		normal = plane_normal(dir, obj->orientation);

	luminosity = compute_lighting(pt, normal, mult_vec3(dir, -1), obj->specular, scene);
	print_argb(luminosity, "luminosity");
	local_color = mult_colors(obj->color, luminosity);
	if (rec <= 0 || obj->reflective.a <= 0)
		return (local_color);
	if (dot_vec3(normal, dir) > 0)
		normal = mult_vec3(normal, -1);
	reflected_ray = reflect_ray(mult_vec3(dir, -1), normal);
	reflected_color = throw_ray(pt, reflected_ray, 0.001, FLT_MAX, rec - 1, scene);
	return (add_colors(mult_colors(local_color, ease_color(obj->reflective, 255)), mult_colors(reflected_color, obj->reflective)));
}

// Normalize the cylinder's orientation vector
// Vector from the cylinder's base position to the point
// Project pt_to_base onto the cylinder's axis
// Check if the point is on the curved surface or the end caps
// Point is on the curved surface
// Point is on the bottom cap
// Point is on the top cap
t_vec3 cylinder_normal(t_vec3 pt, t_object *cylinder)
{
    t_vec3 normal;
    const t_vec3	axis = normalize_vec3(cylinder->orientation);
    const t_vec3	pt_to_base = sub_vec3(pt, cylinder->pos);
    const float		projection = dot_vec3(pt_to_base, axis);
    const t_vec3	proj_vec = mult_vec3(axis, projection);

    if (projection > 0 && projection < cylinder->height)
		normal = normalize_vec3(sub_vec3(pt_to_base, proj_vec));
    else if (projection <= 0) 
		normal = mult_vec3(axis, -1.0f); // Normal points opposite to the axis
    else
		normal = axis; // Normal points in the direction of the axis
    return (normal);
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
