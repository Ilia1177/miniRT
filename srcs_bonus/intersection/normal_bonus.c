/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:57:59 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:58:26 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	triangle_normal(t_ray *ray, t_object *tr)
{
	t_vec4	edge1;
	t_vec4	edge2;
	t_vec4	normal_obj;
	t_mat4	normal_matrix;

	// 1. Compute edges in OBJECT SPACE (original vertices)
	edge1 = sub_vec4(tr->vertice[1], tr->vertice[0]);
	edge2 = sub_vec4(tr->vertice[2], tr->vertice[0]);
	// 2. Calculate object-space normal via cross product
	normal_obj = cross_vec4(edge1, edge2);
	normal_obj = normalize_vec4(normal_obj);
	// 3. Transform normal to WORLD SPACE using inverse transpose matrix
	normal_matrix = mat_transpose(mat_inverse(tr->t_m)); // Inverse transpose = transpose of inverse
	//normal_matrix = mat_transpose(tr->i_m); // Inverse transpose = normal matrix
	ray->n = mat_apply(normal_matrix, normal_obj);
	// 4. Ensure final normal is unit length
	ray->n = normalize_vec4(ray->n);
}

void	plane_normal(t_ray *ray, t_object *pl)
{
	ray->n = normalize_vec4(pl->t_m.k);
}

void	sphere_normal(t_ray *ray, t_object *sp)
{
	const t_mat4	inv = mat_inverse(sp->t_m);
	t_vec4		o = mat_apply(inv, ray->o);
	const t_vec4	normal = sub_vec4(o, (t_vec4){0,0,0,0});

	o.w = 0.0f;
	t_mat4	normal_matrix = mat_transpose(inv); // Inverse transpose = transpose of inverse
	//t_mat4 normal_matrix = mat_transpose(sp->i_m); //Inverse transpose = transpose of inverse
	ray->n = normalize_vec4(mat_apply(normal_matrix, normal));
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
	const t_mat4		inv = mat_inverse(cy->t_m);
	const t_vec4	hit_pt = mat_apply(inv, ray->o); // World → object space
	t_vec4			normal_obj;
	t_mat4			normal_matrix;

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
	normal_matrix = mat_transpose(inv); // Inverse transpose = transpose of inverse
	ray->n = normalize_vec4(mat_apply(normal_matrix, normal_obj));
}
void	hyperboloid_normal(t_ray *ray, t_object *hy)
{
	const t_mat4		inv = mat_inverse(hy->t_m);
	//t_vec4	hit_world;    // Hit point in world space
	t_vec4	hit_obj;      // Hit point in object space
	t_vec4	normal_obj;   // Normal in object space
	t_mat4	normal_mat;   // Inverse transpose matrix for normal transformation

	// 1. Calculate hit point in world space
	//hit_world = add_vec4(ray->o, mult_vec4(ray->d, ray->t));

	// 2. Transform hit point to object space using inverse matrix
	hit_obj = mat_apply(inv, ray->o);

	// 3. Compute gradient (normal) in object space using hyperboloid equation
	normal_obj = (t_vec4){
		.x = hit_obj.x / (hy->scale.x * hy->scale.x),
		.y = hit_obj.y / (hy->scale.y * hy->scale.y),
		.z = -hit_obj.z / (hy->scale.z * hy->scale.z),
		.w = 0.0f
	};

	// 4. Transform normal to world space using inverse transpose matrix
//	normal_mat = mat_transpose(hy->i_m); // Equivalent to inverse transpose
										 //
	normal_mat = mat_transpose(inv); // Inverse transpose = transpose of inverse
	ray->n = mat_apply(normal_mat, normal_obj);

	// 5. Normalize the final normal vector
	ray->n = normalize_vec4(ray->n);
}
void hyperboloid_normal22(t_ray *ray, t_object *object)
{
    // 1. Compute the hyperboloid's axis (W) and total height.
    t_vec4 W = normalize_vec4(object->t_m.k);
    float h = object->height;

    // 2. Compute the hyperboloid's center.
    // (Assuming object->pos is the top, the center is at half the height down along W)
    t_vec4 center = sub_vec4(object->t_m.p, mult_vec4(W, h * 0.5f));

    // 3. Build an orthonormal basis (U, V, W).
    t_vec4 U;
    if (fabs(W.x) > 0.001f || fabs(W.y) > 0.001f)
        U = normalize_vec4((t_vec4){ -W.y, W.x, 0, 0});
    else
        U = normalize_vec4((t_vec4){ 0, 1, 0, 0});
    t_vec4 V = normalize_vec4(cross_vec4(W, U));

    // 4. Transform the point into the hyperboloid's local coordinate system.
    // Compute the relative vector from the hyperboloid's center.
    t_vec4 relative = sub_vec4(ray->o, center);
    float local_x = dot_vec4(relative, U);
    float local_y = dot_vec4(relative, V);
    float local_z = dot_vec4(relative, W);

    // 5. Retrieve hyperboloid scale factors.
    float a = object->scale.x;
    float b = object->scale.y;
    float c = object->scale.z;
    float a2 = a * a, b2 = b * b, c2 = c * c;

    // 6. Compute the local normal using the gradient of F(x,y,z).
    //    F(x,y,z) = x^2/a^2 + y^2/b^2 - z^2/c^2 - 1 = 0.
    //    Therefore, grad F = (2*x/a^2, 2*y/b^2, -2*z/c^2).
    t_vec4 local_normal = {
        2.0f * local_x / a2,
        2.0f * local_y / b2,
        -2.0f * local_z / c2,
        0
    };

    // 7. Transform the local normal back to world coordinates.
    //    The world normal is given by: N = U*local_normal.x + V*local_normal.y + W*local_normal.z.
    t_vec4 world_normal = {
        U.x * local_normal.x + V.x * local_normal.y + W.x * local_normal.z,
        U.y * local_normal.x + V.y * local_normal.y + W.y * local_normal.z,
        U.z * local_normal.x + V.z * local_normal.y + W.z * local_normal.z,
        0
    };

    // 8. Normalize the resulting world normal.
	ray->n = normalize_vec4(world_normal);
}
