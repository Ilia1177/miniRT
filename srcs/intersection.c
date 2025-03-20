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
			if (curr_t < closest_t && curr_t >= t_min && curr_t < t_max)
			{
				if (shadow)
					return (obj);
				closest_t = curr_t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		closest_obj->t = closest_t;
	return (closest_obj);
}

//int	intersect_object(t_vec3 origin, t_vec3 dir, t_object *obj, float *t)
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

// Projection du rayon et origine sur l'axe du cylindre
// Composantes perpendiculaires
// Vérification des bornes du cylindre (en hauteur)
int	intersect_cylinder(t_ray *ray, t_object *cylinder, float *t)
{
    t_quad quad;
    t_vec3 oc;
    t_vec3 axis;
	float	mn[2];
	float	y[2];

	oc = sub_vec3(ray->o, cylinder->pos);
    axis = normalize_vec3(cylinder->orientation);

    mn[0] = dot_vec3(ray->d, axis);
    mn[1] = dot_vec3(oc, axis);
    t_vec3 d_perp = sub_vec3(ray->d, mult_vec3(axis, mn[0]));
    t_vec3 o_perp = sub_vec3(oc, mult_vec3(axis, mn[1]));
    quad = solve_quadratic(o_perp, d_perp, cylinder->radius);
    if (quad.delta < 0)
		return (0);
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];
	if ((y[0] < 0 || y[0] > cylinder->height) && (y[1] < 0 || y[1] > cylinder->height))
        return (0);
	if (y[0] >= 0 && y[0] <= cylinder->height)
        *t = quad.t[0]; 
    else 
        *t = quad.t[1];
    return (1);
}

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
int	intersect_plane(t_ray *ray, t_object *plane, float *t)
{
	float denom = dot_vec3(plane->orientation, ray->d);
	float inter;

	if (fabs(denom) < 1e-6)
		return (0);
	const t_vec3 diff = sub_vec3(plane->pos, ray->o);
	inter = dot_vec3(diff, plane->orientation) / denom;
	if (inter > 0)
	{
		*t = inter;
		return (1);
	}
	return (0);
}
