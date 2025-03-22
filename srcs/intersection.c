#include <miniRT.h>

t_object	*closest_intersect(t_ray *ray, int shadow, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;

	closest_t = t_max;
	curr_t = t_max;
	closest_obj	= NULL;
	while (obj)
	{
		if (intersect_object(ray, obj, &curr_t))
		{
			if (shadow && curr_t >= t_min && curr_t < t_max)
				return (obj);
			if (curr_t < closest_t && curr_t >= t_min && curr_t < t_max)
			{
				closest_t = curr_t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
	{
		closest_obj->t = closest_t;
		if (shadow)
			printf("shadow caught\n");
	}
	return (closest_obj);
}

int	intersect_object(t_ray *ray, t_object *obj, float *t)
{
	if (obj->type == SPHERE && intersect_sphere(ray, obj, t))
		return (1);
	else if (obj->type == CYLINDER && intersect_cylinder(ray, obj, t))
		return (1);
	else if (obj->type == PLANE && intersect_plane(ray, obj, t))
		return (1);
	return (0);
}

int	intersect_sphere(t_ray *ray, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec3	oc;

	oc = sub_vec3(ray->o, sphere->pos);
	quad = solve_quadratic(oc, ray->d, sphere->radius);
	if (quad.delta < 0)
		return (0);
	else if (quad.t[0] < 0 && quad.t[1] < 0)
		return (0);
	else if (quad.t[0] > 0 && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > 0)
		*t = quad.t[1];
//	else if (quad.t[1] > 0)
//		*t = quad.t[1];
//	else
//		*t = quad.t[0];
	return (1);
}

int intersect_cylinder(t_ray *ray, t_object *cylinder, float *t)
{

	t_vec3	center = sub_vec3(cylinder->pos, mult_vec3(cylinder->axis, cylinder->height/2));
	//t_vec3 center = cylinder->pos;
    t_quad quad;
    t_vec3 oc, axis, d_perp, o_perp;
    float mn[2], y[2];

    //oc = sub_vec3(ray->o, cylinder->pos);
    oc = sub_vec3(ray->o, center);
    axis = normalize_vec3(cylinder->axis);

    // Project ray direction and origin onto the cylinder's axis
    mn[0] = dot_vec3(ray->d, axis);
    mn[1] = dot_vec3(oc, axis);
    d_perp = sub_vec3(ray->d, mult_vec3(axis, mn[0]));
    o_perp = sub_vec3(oc, mult_vec3(axis, mn[1]));

    // Solve quadratic equation for intersection points
    quad = solve_quadratic(o_perp, d_perp, cylinder->radius);
    if (quad.delta < 0)
        return (0); // No real intersection

    // Compute y-coordinates of intersection points along the cylinder's axis
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];

    // Check if intersections are within the cylinder's height
    int valid0 = (y[0] >= 0 && y[0] <= cylinder->height);
    int valid1 = (y[1] >= 0 && y[1] <= cylinder->height);

    // Ensure the correct intersection is chosen
    if (!valid0 && !valid1)
        return (0);
    if (valid0 && valid1)
    {
        // If inside the object, pick the second intersection (exit point)
		if (quad.t[0] > 0.001f && quad.t[0] < quad.t[1])
			*t = quad.t[0];
		else if (quad.t[1] > 0)
			*t = quad.t[1];
    }
    else
    {
        // Otherwise, pick the valid intersection
		if (valid0 && quad.t[0] < quad.t[1])
			*t = quad.t[0];
		else if (quad.t[1] > 0)
			*t = quad.t[1];
       // *t = valid0 ? quad.t[0] : quad.t[1];
    }
    // Ensure that the intersection is in the forward direction of the ray
	if (*t < 0)
		return (0); // Intersection is behind the ray's origin
    return (1);
}

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
int	intersect_plane(t_ray *ray, t_object *plane, float *t)
{
	const float denom = dot_vec3(plane->axis, ray->d);
	t_vec3		diff;
	float		inter;

	if (fabs(denom) < 1e-6)
		return (0);
	diff = sub_vec3(plane->pos, ray->o);
	inter = dot_vec3(diff, plane->axis) / denom;
	if (inter > 0)
	{
		*t = inter;
		return (1);
	}
	return (0);
}
