#include <miniRT.h>

t_object	*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;
	float		*t;

	(void)t_max;
	(void)t_min;
	closest_t = FLT_MAX;
	curr_t = FLT_MAX;
	closest_obj	= NULL;
	while (obj)
	{
		t = obj->t;
		if(intersect_object(origin, dir, obj, &curr_t))
		{
			 if (t[0] >= t_min && t[0] <= t_max && t[0] < closest_t) 
			 { 
			 	closest_t = t[0]; 
			 	closest_obj = obj; 
			 } 
			 if (t[1] >= t_min && t[1] <= t_max && t[1] < closest_t) 
			 { 
			 	closest_t = t[1]; 
			 	closest_obj = obj; 
			 }
		}
		obj = obj->next;
	}
	if (closest_obj)
		closest_obj->closest_t = closest_t;
	return (closest_obj);
}

int	intersect_object(t_vec3 origin, t_vec3 dir, t_object *obj, float *t)
{
	if (obj->type == SPHERE && intersect_sphere(origin, dir, obj, t))
		return (1);
	else if (obj->type == CYLINDER && intersect_cylinder(origin, dir, obj, t))
		return (1);
	else if (obj->type == PLANE && intersect_plane(origin, dir, obj))
		return (1);
	return (0);
}

int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec3	oc;

	oc = sub_vec3(origin, sphere->pos);
	quad = solve_quadratic(oc, dir, sphere->radius);
	sphere->t[0] = quad.t[0];
	sphere->t[1] = quad.t[1];
	sphere->closest_t = FLT_MAX;
	if (quad.delta < 0)
		return (0);
	if (quad.t[0] < 0 && quad.t[1] < 0)
		return (0);
	if (quad.t[0] >= 0 && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] >= 0 && quad.t[1] < quad.t[0])
		*t = quad.t[1];
	return (1);
}

// Projection du rayon et origine sur l'axe du cylindre
// Composantes perpendiculaires
// Vérification des bornes du cylindre (en hauteur)
int	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *cylinder, float *t)
{
    t_quad quad;
    t_vec3 oc;
    t_vec3 axis;
	float	mn[2];
	float	y[2];

	//(void)t;
	oc = sub_vec3(origin, cylinder->pos);
    axis = normalize_vec3(cylinder->orientation);

    mn[0] = dot_vec3(dir, axis);
    mn[1] = dot_vec3(oc, axis);
    t_vec3 d_perp = sub_vec3(dir, mult_vec3(axis, mn[0]));
    t_vec3 o_perp = sub_vec3(oc, mult_vec3(axis, mn[1]));
    quad = solve_quadratic(o_perp, d_perp, cylinder->radius);
	cylinder->t[0] = quad.t[0];
	cylinder->t[1] = quad.t[1];
	cylinder->closest_t = FLT_MAX;
    if (quad.delta < 0)
		return (0);
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];
	if ((y[0] < 0 || y[0] > cylinder->height) && (y[1] < 0 || y[1] > cylinder->height))
        return (0);
	/* if (y[0] >= 0 && y[0] <= cylinder->height) { */
        /* *t = quad.t[0]; */
    /* } else { */
        /* *t = quad.t[1]; */
    /* } */
	if (quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > 0)
		*t = quad.t[1];
    return (1);
}

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
int	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *plane)
{
	const t_vec3	diff = sub_vec3(plane->pos, origin);
	const float		denom = dot_vec3(plane->orientation, dir);

	//t_vec3	normal = sub_vec3(pt, obj->pos);
	//normal = normalize_vec3(normal);
	if (fabs(denom) < 1e-6)
		return (0);
	plane->t[0] = dot_vec3(diff, normalize_vec3(plane->orientation)) / denom;
	plane->t[1] = FLT_MAX;
	if (plane->t[0] > 0)
		return (1);
	return (0);
}
