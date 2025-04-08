#include <miniRT_bonus.h>

// Helper function to check if a wall intersection is within the cylinder's height
void check_tube(float t, t_vec3 origin, t_vec3 dir, float height, float *t_min)
{
	float	z;

    if (t > EPSILON)
	{
		t_vec3 hit_point = add_vec3(origin, mult_vec3(dir, t));
        z = dot_vec3(hit_point, (t_vec3){0, 0, 1, 0}); // Project onto cylinder's axis
        if (z >= 0 && z <= height) 
            *t_min = fminf(*t_min, t);
    }
}

// Helper function to check intersections with the end caps
void check_cap(float cap_z, t_vec3 origin, t_vec3 dir, float radius, float *t_min)
{
	float	t;
	float	x;
	float	y;

    if (fabsf(dir.z) < EPSILON)
		return;
    t = (cap_z - origin.z) / dir.z;
    if (t > EPSILON)
	{
        x = origin.x + t * dir.x;
        y = origin.y + t * dir.y;
        if (x*x + y*y <= radius*radius)
            *t_min = fminf(*t_min, t);
    }
}

// 1. Transform ray to object space
// 2. Calculate coefficients for the infinite cylinder equation
// 3. Cylinder is aligned along Z-axis in object space
// 4. Project direction and origin onto the plane perpendicular to the cylinder's axis
// 5. Check intersections with the cylinder walls (within height range)
// 6. Check intersections with the end caps (z=0 and z=height)
int intersect_cylinder(t_ray *ray, t_object *cylinder, float *t)
{
    t_vec3 origin = mat_apply(cylinder->i_m, ray->o);
    t_vec3 dir = mat_apply(cylinder->i_m, ray->d);
    t_vec3 axis = (t_vec3){0, 0, 1, 0};  
    t_vec3 d_proj = sub_vec3(dir, mult_vec3(axis, dot_vec3(dir, axis)));
    t_vec3 o_proj = sub_vec3(origin, mult_vec3(axis, dot_vec3(origin, axis)));
    const float a = dot_vec3(d_proj, d_proj);
    const float b = 2 * dot_vec3(d_proj, o_proj);
    const float c = dot_vec3(o_proj, o_proj) - (cylinder->radius * cylinder->radius);
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
		return 0;
    float sqrt_disc = sqrtf(discriminant);
    float t1 = (-b - sqrt_disc) / (2 * a);
    float t2 = (-b + sqrt_disc) / (2 * a);
    float t_min = INFINITY;
    check_tube(t1, origin, dir, cylinder->height, &t_min);
    check_tube(t2, origin, dir, cylinder->height, &t_min);
    check_cap(0, origin, dir, cylinder->radius, &t_min);
    check_cap(cylinder->height, origin, dir, cylinder->radius, &t_min);
    if (t_min < INFINITY)
	{
        *t = t_min;
        return 1;
    }
    return 0;
}


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
		closest_obj->t = closest_t;
	return (closest_obj);
}

// ray equation p = o + t * d;
// with :
// p = point
// o = origin of the ray
// t = coeff on direction
// d = direction of the ray
int	intersect_object(t_ray *ray, t_object *obj, float *t)
{
	if (obj->type == SPHERE && intersect_sphere(ray, obj, t))
		return (1);
	else if (obj->type == CYLINDER && intersect_cylinder(ray, obj, t))
		return (1);
	else if (obj->type == PLANE && intersect_plane(ray, obj, t))
		return (1);
	else if (obj->type == HYPERBOL && intersect_hyperboloid(ray, obj, t))
		return (1);
	return (0);
}

// Equation of sphere:
// dist(p, sphere->center) = rayon^2
int	intersect_sphere(t_ray *ray, t_object *sp, float *t)
{
	t_quad			quad;
	const t_vec3	origin = mat_apply(sp->i_m, ray->o);
	t_vec3	dir = mat_apply(sp->i_m, ray->d);

	quad = solve_quadratic(origin, dir, sp->radius);
	if (quad.delta < 0.0f)
		return (0);
	else if (quad.t[0] < EPSILON && quad.t[1] < EPSILON)
		return (0);
	else if (quad.t[0] > EPSILON && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > EPSILON)
		*t = quad.t[1];
//	else if (quad.t[1] > 0)
//		*t = quad.t[1];
//	else
//		*t = quad.t[0];
	return (1);
}

// Si denom ≈ 0, le rayon est parallèle au plan => pas d'intersection
// 1. dot_vec3(axis, dir) -> ray perpendiculaire au plan, == we dont see the plane
// 2 
int	intersect_plane(t_ray *ray, t_object *pl, float *t)
{
	const t_vec3	origin = mat_apply(pl->i_m, ray->o);
	const t_vec3	dir = mat_apply(pl->i_m, ray->d);
	float			inter;

	if (fabs(dir.z) < EPSILON)
		return (0);
	inter = -origin.z / dir.z;
	if (inter > EPSILON)
	{
		*t = inter;
		return (1);
	}
	return (0);
}

int intersect_hyperboloid(t_ray *ray, t_object *object, float *t)
{
    // 1. Compute the hyperboloid's axis (W) and total height h.
    t_vec3 W = normalize_vec3(object->axis);
    float h = object->height;

    // 2. Compute the hyperboloid's center.
    // Here we assume object->pos is the top, so the center is halfway down the axis.
    t_vec3 center = sub_vec3(object->pos, mult_vec3(W, h * 0.5f));

    // 3. Build an orthonormal basis (U, V, W).
    t_vec3 U;
    // Choose an arbitrary vector not parallel to W:
    if (fabs(W.x) > 0.001f || fabs(W.y) > 0.001f)
        U = normalize_vec3((t_vec3){ -W.y, W.x, 0, 0 });
    else
        U = normalize_vec3((t_vec3){ 0, 1, 0, 0});
    t_vec3 V = normalize_vec3(cross_vec3(W, U));

    // 4. Transform the ray into the hyperboloid's local space.
    // Compute oc = ray origin relative to center.
    t_vec3 oc = sub_vec3(ray->o, center);
    // Local coordinates for origin:
    float ox = dot_vec3(oc, U);
    float oy = dot_vec3(oc, V);
    float oz = dot_vec3(oc, W);
    // Local coordinates for direction:
    float dx = dot_vec3(ray->d, U);
    float dy = dot_vec3(ray->d, V);
    float dz = dot_vec3(ray->d, W);

    // 5. Get hyperboloid scale factors: a, b, c.
    float a = object->scale.x;
    float b = object->scale.y;
    float c = object->scale.z;
    float a2 = a * a, b2 = b * b, c2 = c * c;

    // 6. Form the quadratic equation coefficients.
    // Equation: ((ox + t*dx)^2)/(a^2) + ((oy + t*dy)^2)/(b^2) - ((oz + t*dz)^2)/(c^2) - 1 = 0
    float A = (dx*dx)/a2 + (dy*dy)/b2 - (dz*dz)/c2;
    float B = 2.0f * ( (ox*dx)/a2 + (oy*dy)/b2 - (oz*dz)/c2 );
    float C = (ox*ox)/a2 + (oy*oy)/b2 - (oz*oz)/c2 - 1.0f;

    // 7. Solve the quadratic equation A*t^2 + B*t + C = 0.
    float discriminant = B*B - 4.0f * A * C;
    if (discriminant < 0)
        return 0; // No real intersection.
    float sqrt_disc = sqrtf(discriminant);
    float t0 = (-B - sqrt_disc) / (2.0f * A);
    float t1 = (-B + sqrt_disc) / (2.0f * A);

    // 8. Choose the smallest positive t.
    float t_candidate = FLT_MAX;
    if (t0 > 0.001f)
        t_candidate = t0;
    if (t1 > 0.001f && t1 < t_candidate)
        t_candidate = t1;
    if (t_candidate == FLT_MAX)
        return 0; // Both intersections are behind the ray.

    // 9. Check height limits.
    // The local z-coordinate of the intersection is:
    float z_hit = oz + t_candidate * dz;
    // Only accept intersections with 0 <= z_hit <= h.
    if (z_hit < -h || z_hit > h)
		return 0;

    *t = t_candidate;
    return 1;
}

