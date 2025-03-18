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

t_vec3	sphere_normal(t_vec3 pt, t_vec3 origin, t_vec3 dir, t_object *sphere)
{
	t_vec3	normal;

//	if (dot_vec3(normal, dir) > 0.0f)
//		normal  = mult_vec3(normal, -1);
	normal = normalize_vec3(sub_vec3(pt, sphere->pos));
//	if (dist_vec3(pt, sphere->pos) < sphere->radius)
//		normal = mult_vec3(normal, -1);
	return (normal);
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
		normal = axis; //Normal points in the direction of the axis
    return (normal);
}
