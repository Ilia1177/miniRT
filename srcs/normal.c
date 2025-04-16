/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:36:34 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 13:47:11 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_vec4	compute_normal(t_vec4 P, t_object *cylinder)
{
	const t_vec4	center = sub_vec4(cylinder->pos,
			mult_vec4(cylinder->axis, cylinder->height / 2));
	const t_vec4	x = sub_vec4(P, center);
	const float		m = dot_vec4(x, cylinder->axis);
	const t_vec4	n = normalize_vec4(sub_vec4(x,
				mult_vec4(cylinder->axis, m)));

	return (n);
}

void	plane_normal(t_ray *ray, t_object *plane)
{
	if (dot_vec4(plane->axis, ray->d) > 0.0f)
		ray->n = mult_vec4(plane->axis, -1.0f);
	else
		ray->n = plane->axis;
}

void	sphere_normal(t_ray *ray, t_object *sphere)
{
	ray->n = normalize_vec4(sub_vec4(ray->o, sphere->pos));
}

// Normalize the cylinder's axis vector
// Vector from the cylinder's base position to the point
// Project pt_to_base onto the cylinder's axis
// Check if the point is on the curved surface or the end caps
// Point is on the curved surface
// Point is on the bottom cap
// Point is on the top cap
void	cylinder_normal(t_ray *ray, t_object *cylinder)
{
	//t_vec4	center = sub_vec3(cylinder->pos, mult_vec4(cylinder->axis, cylinder->height/2));
	const t_vec4	center = cylinder->pos;
	const t_vec4	axis = normalize_vec4(cylinder->axis);
	const t_vec4	pt_to_base = sub_vec4(ray->o, center);
	const float		projection = dot_vec4(pt_to_base, axis);
	const t_vec4	proj_vec = mult_vec4(axis, projection);

	if (projection > 0.0f && projection < cylinder->height)
		ray->n = normalize_vec4(sub_vec4(pt_to_base, proj_vec));
	else if (projection <= 0.0f)
		ray->n = mult_vec4(axis, -1.0f);
	else
		ray->n = axis;
	//	ray->n = compute_normal(ray->o, cylinder);
}
