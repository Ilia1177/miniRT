#include <miniRT_bonus.h>

void	plane_normal(t_ray *ray, t_object *pl)
{
	const t_vec3	axis = {0, 0, 1, 0};
	const t_vec3	dir = mat_apply(pl->i_m, ray->d);

	if (dot_vec3(axis, dir) < EPSILON)
		ray->n = mult_vec3(axis, -1.0f);
	else
		ray->n = axis;
	print_vec3(ray->n, "plane normal:");
}

void	sphere_normal(t_ray *ray, t_object *sp)
{
	const t_vec3	origin = mat_apply(sp->i_m, ray->o);
	const t_vec3	zero_v = {0, 0, 0, 0};

	ray->n = normalize_vec3(sub_vec3(zero_v, origin));
}

void	cylinder_normal(t_ray *ray, t_object *cylinder)
{
    // Transform hit point to object space
    t_vec3 obj_hit = mat_apply(cylinder->i_m, ray->o);
    
    // Calculate normal in object space
    t_vec3 normal_obj;
    const float eps = 1e-6;
    
    // Check if we're hitting an end cap
    if (fabsf(obj_hit.z) < EPSILON || fabsf(obj_hit.z - cylinder->height) < eps) {
        // End cap normal depends on which cap we hit
        normal_obj = (t_vec3){0, 0, (obj_hit.z < eps) ? -1.0f : 1.0f, 0};
    } else {
        // Cylinder body normal (radial direction)
        normal_obj = (t_vec3){obj_hit.x, obj_hit.y, 0, 0};
        normal_obj = normalize_vec3(normal_obj);
    }
    // Transform normal back to world space using inverse transpose matrix
    t_matrix inv_transpose = mat_transpose(cylinder->i_m);
    t_vec3 normal_world = mat_apply(inv_transpose, normal_obj);
    ray->n = normalize_vec3(normal_world);
}

// Normalize the cylinder's axis vector
// Vector from the cylinder's base position to the point
// Project pt_to_base onto the cylinder's axis
// Check if the point is on the curved surface or the end caps
// Point is on the curved surface
// Point is on the bottom cap
// Point is on the top cap
void	_OLD_unsed_function(t_ray *ray, t_object *cylinder)
{
	//t_vec3	center = sub_vec3(cylinder->pos, mult_vec3(cylinder->axis, cylinder->height/2));
	t_vec3	center = cylinder->pos;
    const t_vec3	axis = normalize_vec3(cylinder->axis);
    const t_vec3	pt_to_base = sub_vec3(ray->o, center);
    const float		projection = dot_vec3(pt_to_base, axis);
    const t_vec3	proj_vec = mult_vec3(axis, projection);

	if (projection > 0.001f && projection < cylinder->height)
		ray->n = normalize_vec3(sub_vec3(pt_to_base, proj_vec));
	else if (projection <= 0.001f) 
		ray->n = mult_vec3(axis, -1.0f); // Normal points opposite to the axis
	else
	   ray->n = axis; //Normal points in the direction of the axis
//	ray->n = compute_normal(ray->o, cylinder);
}

void hyperboloid_normal(t_ray *ray, t_object *object)
{
    // 1. Compute the hyperboloid's axis (W) and total height.
    t_vec3 W = normalize_vec3(object->axis);
    float h = object->height;

    // 2. Compute the hyperboloid's center.
    // (Assuming object->pos is the top, the center is at half the height down along W)
    t_vec3 center = sub_vec3(object->pos, mult_vec3(W, h * 0.5f));

    // 3. Build an orthonormal basis (U, V, W).
    t_vec3 U;
    if (fabs(W.x) > 0.001f || fabs(W.y) > 0.001f)
        U = normalize_vec3((t_vec3){ -W.y, W.x, 0, 0});
    else
        U = normalize_vec3((t_vec3){ 0, 1, 0, 0});
    t_vec3 V = normalize_vec3(cross_vec3(W, U));

    // 4. Transform the point into the hyperboloid's local coordinate system.
    // Compute the relative vector from the hyperboloid's center.
    t_vec3 relative = sub_vec3(ray->o, center);
    float local_x = dot_vec3(relative, U);
    float local_y = dot_vec3(relative, V);
    float local_z = dot_vec3(relative, W);

    // 5. Retrieve hyperboloid scale factors.
    float a = object->scale.x;
    float b = object->scale.y;
    float c = object->scale.z;
    float a2 = a * a, b2 = b * b, c2 = c * c;

    // 6. Compute the local normal using the gradient of F(x,y,z).
    //    F(x,y,z) = x^2/a^2 + y^2/b^2 - z^2/c^2 - 1 = 0.
    //    Therefore, grad F = (2*x/a^2, 2*y/b^2, -2*z/c^2).
    t_vec3 local_normal = {
        2.0f * local_x / a2,
        2.0f * local_y / b2,
        -2.0f * local_z / c2,
        0
    };

    // 7. Transform the local normal back to world coordinates.
    //    The world normal is given by: N = U*local_normal.x + V*local_normal.y + W*local_normal.z.
    t_vec3 world_normal = {
        U.x * local_normal.x + V.x * local_normal.y + W.x * local_normal.z,
        U.y * local_normal.x + V.y * local_normal.y + W.y * local_normal.z,
        U.z * local_normal.x + V.z * local_normal.y + W.z * local_normal.z,
        0
    };

    // 8. Normalize the resulting world normal.
	ray->n = normalize_vec3(world_normal);
}
