#include <miniRT_bonus.h>

void	plane_normal(t_ray *ray, t_object *pl)
{
	ray->n = normalize_vec3(pl->t_m.k);
}

void	sphere_normal(t_ray *ray, t_object *sp)
{
	ray->n = normalize_vec3(sub_vec3(ray->o, sp->t_m.p));
}

/*******************************************************************************
* 1. Transform hit point to object space
* 2. Calculate normal in object space
* 3. Check if we're hitting an end cap
* 4. End cap normal depends on which cap we hit
* 5. Transform normal back to world space using inverse transpose matrix
*******************************************************************************/
void	cylinder_normal(t_ray *ray, t_object *cy)
{
    t_vec3 hit_pt = mat_apply(cy->i_m, ray->o);
    t_vec3 normal_obj;
    
   if (fabsf(hit_pt.z) < EPSILON || fabsf(hit_pt.z - cy->height) < EPSILON)
   {
	   if (hit_pt.z < EPSILON)
			normal_obj = (t_vec3){0, 0, -1.0f, 0};
	   else
			normal_obj = (t_vec3){0, 0, 1.0f, 0};
   }
   else
   {
        normal_obj = (t_vec3){hit_pt.x, hit_pt.y, 0, 0};
        normal_obj = normalize_vec3(normal_obj);
   }	
   t_vec3 normal_world = mat_apply(cy->t_m, normal_obj);
   ray->n = normalize_vec3(normal_world);
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
