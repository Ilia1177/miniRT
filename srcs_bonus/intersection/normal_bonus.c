/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:57:59 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 11:05:29 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// 1. Compute edges in OBJECT SPACE (original vertices)
// 2. Calculate object-space normal via cross product
// 3. Transform normal to WORLD SPACE using inverse transpose matrix
//normal_matrix = mat_transpose(tr->i_m); // Inverse transpose = normal matrix
// 4. Ensure final normal is unit length
void	triangle_normal(t_ray *ray, t_object *tr)
{
	const t_vec4	edge1 = sub_vec4(tr->vertice[1], tr->vertice[0]);
	const t_vec4	edge2 = sub_vec4(tr->vertice[2], tr->vertice[0]);
	const t_mat4	normal_matrix = mat_transpose(mat_inverse(tr->t_m));
	const t_vec4	normal_obj = normalize_vec4(cross_vec4(edge1, edge2));

	ray->n = normalize_vec4(mat_apply(normal_matrix, normal_obj));
	ray->n.w = 0.0f;
}

void	plane_normal(t_ray *ray, t_object *pl)
{
	ray->n = normalize_vec4(pl->t_m.k);
}

void	sphere_normal(t_ray *ray, t_object *sp)
{
	const t_mat4	inv = mat_inverse(sp->t_m);
	const t_mat4	normal_matrix = mat_transpose(inv);
	const t_vec4	hp = mat_apply(inv, ray->o);
	const t_vec4	normal = sub_vec4(hp, (t_vec4){0.0f, 0.0f, 0.0f, 1.0f});

	ray->n = normalize_vec4(mat_apply(normal_matrix, normal));
	print_vec4(ray->n, "sphere 2 - normal:");
	ray->n.w = 0.0f;
}

/*******************************************************************************
 * 1. Transform hit point to object space
 * 3. Check if we're hitting an end cap 
 * 4. End cap normal depends on which cap we hit
 * 5. Tube body: radial direction (x, y, 0) in object space
 * 6. Transform normal to world space using inverse transpose matrix
*******************************************************************************/
void	cylinder_normal(t_ray *ray, t_object *cy)
{
	const t_mat4	inv = mat_inverse(cy->t_m);
	const t_mat4	normal_matrix = mat_transpose(inv);
	const t_vec4	hit_pt = mat_apply(inv, ray->o);
	t_vec4			normal_obj;

	if (fabsf(hit_pt.z + 0.5f) < EPSILON || fabsf(hit_pt.z - 0.5f) < EPSILON)
	{
		if (hit_pt.z < 0)
			normal_obj = (t_vec4){0, 0, -1.0f, 0};
		else
			normal_obj = (t_vec4){0, 0, 1.0f, 0};
	}
	else
	{
		normal_obj = (t_vec4){hit_pt.x, hit_pt.y, 0, 0};
		normal_obj = normalize_vec4(normal_obj);
	}
	ray->n = normalize_vec4(mat_apply(normal_matrix, normal_obj));
	ray->n.w = 0.0f;
}

// 1. Calculate hit point in world space
// 2. Transform hit point to object space using inverse matrix
// 3. Compute gradient (normal) in object space using hyperboloid equation
// 4. Transform normal to world space using inverse transpose matrix
void	hyperboloid_normal(t_ray *ray, t_object *hy)
{
	const t_mat4	inv = mat_inverse(hy->t_m);
	t_vec4			hit_obj;
	t_vec4			normal_obj;
	const t_mat4	normal_mat = mat_transpose(inv);

	hit_obj = mat_apply(inv, ray->o);
	normal_obj = (t_vec4){
		.x = hit_obj.x / (hy->scale.x * hy->scale.x),
		.y = hit_obj.y / (hy->scale.y * hy->scale.y),
		.z = -hit_obj.z / (hy->scale.z * hy->scale.z),
		.w = 0.0f
	};
	ray->n = normalize_vec4(mat_apply(normal_mat, normal_obj));
	ray->n.w = 0.0f;
}
