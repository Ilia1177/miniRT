#include <miniRT.h>

t_object	*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;
	//float		*t;

	closest_t = FLT_MAX;
	curr_t = FLT_MAX;
	closest_obj	= NULL;
	while (obj)
	{
		//t = obj->t;
		if(intersect_object(origin, dir, obj, &curr_t))
		{
			printf("intersect\n");
			printf("curr_t: %f\n", curr_t);
			if (curr_t < closest_t && curr_t >= t_min && curr_t < t_max)
			{
				closest_t = curr_t;
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
	else if (obj->type == PLANE && intersect_plane(origin, dir, obj, t))
		return (1);
	return (0);
}

int	intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec3	oc;

	oc = sub_vec3(origin, sphere->pos);
	quad = solve_quadratic(oc, dir, sphere->radius);
	if (quad.delta < 0)
		return (0);
	printf("delta: %f\n", quad.delta);
//	if (quad.t[0] < 0 && quad.t[1] < 0)
//		return (0);
	if (quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] < quad.t[0])
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
int	intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *cylinder, float *t)
{
    t_quad quad;
    t_vec3 oc;
    t_vec3 axis;
	float	mn[2];
	float	y[2];

	oc = sub_vec3(origin, cylinder->pos);
    axis = normalize_vec3(cylinder->orientation);

    mn[0] = dot_vec3(dir, axis);
    mn[1] = dot_vec3(oc, axis);
    t_vec3 d_perp = sub_vec3(dir, mult_vec3(axis, mn[0]));
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

int	intersect_plane3(t_vec3 l0, t_vec3 l, t_object *plane, float *t)
{

	float denom = dot_vec3(plane->orientation, l);
	if (fabs(denom) > 1e-6)
	{
		t_vec3 p0l0 = sub_vec3(normalize_vec3(sub_vec3(plane->pos, l0)), l0);
		*t = dot_vec3(p0l0, plane->orientation);
		return (1);
	}
	return (0);

}
// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
int	intersect_plane(t_vec3 origin, t_vec3 dir, t_object *plane, float *t)
{
	float denom = dot_vec3(plane->orientation, dir);
	float inter;

	if (fabs(denom) < 1e-6)
		return (0);
	const t_vec3 diff = sub_vec3(plane->pos, origin);
	inter = dot_vec3(diff, plane->orientation) / denom;
	if (inter > 0)
	{
		*t = inter;
		return (1);
	}
	return (0);
}

int	intersect_plane4(t_vec3 o, t_vec3 dir, t_object *pl, float *hit)
{
	float	denom;
	t_vec3	tmp;
	t_vec3	pt;
	float	t_hit;

	denom = dot_vec3(pl->orientation, dir);
	if (denom == 0)
		return (0);
	tmp = sub_vec3(o, pl->pos);
	t_hit = dot_vec3(tmp, pl->orientation) / denom;
	if (t_hit < 0.001)
		return (0);
	pt = add_vec3(mult_vec3(dir, t_hit), o);
	if (dot_vec3(pl->orientation, dir) > 0)
		*hit = t_hit;
	return (1);
}



int	intersect_plane2(t_vec3 origin, t_vec3 dir, t_object *plane, float *t)
{
	const t_vec3	diff = sub_vec3(plane->pos, origin);
	const float		denom = dot_vec3(plane->orientation, dir);
	float			intersect;

	if (fabs(denom) < 1e-6)
		return (0);
	intersect = dot_vec3(diff, plane->orientation) / denom;
	if (intersect > 0)
	{
		*t = intersect;
		return (1);
	}
	return (0);
}
