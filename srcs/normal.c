#include <miniRT.h>
t_vec3 compute_normal(t_vec3 P, t_object *cylinder)
{
	t_vec3	center = sub_vec3(cylinder->pos, mult_vec3(cylinder->axis, cylinder->height/2));
    t_vec3 X = sub_vec3(P, center);
    float m = dot_vec3(X, cylinder->axis);
    t_vec3 N = normalize_vec3(sub_vec3(X, mult_vec3(cylinder->axis, m)));
    return N;
}

void	plane_normal(t_ray *ray, t_object *plane)
{
	if (dot_vec3(plane->axis, ray->d) > 0.0f)
		ray->n = mult_vec3(plane->axis, -1.0f);
	else
		ray->n = plane->axis;
}

void	sphere_normal(t_ray *ray, t_object *sphere)
{
	ray->n = normalize_vec3(sub_vec3(ray->o, sphere->pos));
}


// add .
// Normalize the cylinder's axis vector
// Vector from the cylinder's base position to the point
// Project pt_to_base onto the cylinder's axis
// Check if the point is on the curved surface or the end caps
// Point is on the curved surface
// Point is on the bottom cap
// Point is on the top cap
void	cylinder_normal(t_ray *ray, t_object *cylinder)
{
	t_vec3	center = sub_vec3(cylinder->pos, mult_vec3(cylinder->axis, cylinder->height/2));
	//t_vec3	center = cylinder->pos;
    const t_vec3	axis = normalize_vec3(cylinder->axis);
    const t_vec3	pt_to_base = sub_vec3(ray->o, center);
    const float		projection = dot_vec3(pt_to_base, axis);
    const t_vec3	proj_vec = mult_vec3(axis, projection);

	if (projection > 0.0f && projection < cylinder->height)
		ray->n = normalize_vec3(sub_vec3(pt_to_base, proj_vec));
	else if (projection <= 0.0f) 
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
