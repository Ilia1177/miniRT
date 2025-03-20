#include <miniRT.h>

void	plane_normal(t_ray *ray, t_object *plane)
{
	if (dot_vec3(plane->orientation, ray->d) > 0.0f)
		ray->n = mult_vec3(plane->orientation, -1.0f);
	else
		ray->n = plane->orientation;
}

void	sphere_normal(t_ray *ray, t_object *sphere)
{
	ray->n = normalize_vec3(sub_vec3(sphere->pt, sphere->pos));
}

// Normalize the cylinder's orientation vector
// Vector from the cylinder's base position to the point
// Project pt_to_base onto the cylinder's axis
// Check if the point is on the curved surface or the end caps
// Point is on the curved surface
// Point is on the bottom cap
// Point is on the top cap
void	cylinder_normal(t_ray *ray, t_object *cylinder)
{
    const t_vec3	axis = normalize_vec3(cylinder->orientation);
    const t_vec3	pt_to_base = sub_vec3(cylinder->pt, cylinder->pos);
    const float		projection = dot_vec3(pt_to_base, axis);
    const t_vec3	proj_vec = mult_vec3(axis, projection);

	if (projection > 0 && projection < cylinder->height)
		ray->n = normalize_vec3(sub_vec3(pt_to_base, proj_vec));
	else if (projection <= 0) 
		ray->n = mult_vec3(axis, -1.0f); // Normal points opposite to the axis
    else
	   ray->n = axis; //Normal points in the direction of the axis
}

