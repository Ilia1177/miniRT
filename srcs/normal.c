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

