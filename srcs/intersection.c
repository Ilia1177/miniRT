#include <miniRT.h>

// Helper function to check if a wall intersection is within the cylinder's height
void check_intersection(float t, t_vec3 origin, t_vec3 dir, float height, float *t_min)
{
    if (t > EPSILON)
	{
		t_vec3 hit_point = add_vec3(origin, mult_vec3(dir, t));
        float z = dot_vec3(hit_point, (t_vec3){0, 0, 1, 0}); // Project onto cylinder's axis
        //float z = origin.z + t * dir.z;
        if (z >= 0 && z <= height) {
            *t_min = fminf(*t_min, t);
        }
    }
}

// Helper function to check intersections with the end caps
void check_cap(float cap_z, t_vec3 origin, t_vec3 dir, float radius, float *t_min)
{
    if (fabsf(dir.z) < EPSILON) return;  // Ray is parallel to the cap

    float t = (cap_z - origin.z) / dir.z;
    if (t > EPSILON)
	{
        float x = origin.x + t * dir.x;
        float y = origin.y + t * dir.y;
        if (x*x + y*y <= radius*radius) {
            *t_min = fminf(*t_min, t);
        }
    }
}

int intersect_cylinder(t_ray *ray, t_object *cylinder, float *t)
{
    // Transform ray to object space
	ray->o.w = 1;
	ray->d.w = 0;
    t_vec3 transformed_origin = mat_apply(cylinder->i_m, ray->o);
    t_vec3 transformed_direction = mat_apply(cylinder->i_m, ray->d);

    // Calculate coefficients for the infinite cylinder equation
    t_vec3 axis = (t_vec3){0, 0, 1, 0};  // Cylinder is aligned along Z-axis in object space
    t_vec3 oc = transformed_origin;  // Origin to cylinder center (already in object space)

    // Project direction and origin onto the plane perpendicular to the cylinder's axis
    t_vec3 d_proj = sub_vec3(transformed_direction, mult_vec3(axis, dot_vec3(transformed_direction, axis)));
    t_vec3 oc_proj = sub_vec3(oc, mult_vec3(axis, dot_vec3(oc, axis)));

    float a = dot_vec3(d_proj, d_proj);
    float b = 2 * dot_vec3(d_proj, oc_proj);
    float c = dot_vec3(oc_proj, oc_proj) - (cylinder->radius * cylinder->radius);

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return 0;  // No intersection with infinite cylinder

    float sqrt_disc = sqrtf(discriminant);
    float t1 = (-b - sqrt_disc) / (2 * a);
    float t2 = (-b + sqrt_disc) / (2 * a);

    float t_min = INFINITY;

    // Check intersections with the cylinder walls (within height range)
    check_intersection(t1, transformed_origin, transformed_direction, cylinder->height, &t_min);
    check_intersection(t2, transformed_origin, transformed_direction, cylinder->height, &t_min);

    // Check intersections with the end caps (z=0 and z=height)
    check_cap(0, transformed_origin, transformed_direction, cylinder->radius, &t_min);
    check_cap(cylinder->height, transformed_origin, transformed_direction, cylinder->radius, &t_min);

    if (t_min < INFINITY) {
        *t = t_min;
        return 1;
    }

    return 0;  // No valid intersection
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

int	intersect_sphere_LOCAL_SPACE(t_ray *ray, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec3	oc;
	const t_vec3	axis = normalize_vec3(sphere->t_m.k);
	const t_vec3	trans_o = mat_apply(sphere->i_m, ray->o);
	const t_vec3	trans_d = mat_apply(sphere->i_m, ray->d);

	oc = sub_vec3(ray->o, (t_vec3) {0, 0, 0, 0});
	quad = solve_quadratic(oc, trans_d, mag_vec3(sphere->t_m.k) / 2);
	if (quad.delta < 0.0f)
		return (0);
	else if (quad.t[0] < 0.001f && quad.t[1] < 0.0f)
		return (0);
	else if (quad.t[0] > 0.001f && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > 0.00f)
		*t = quad.t[1];
//	else if (quad.t[1] > 0)
//		*t = quad.t[1];
//	else
//		*t = quad.t[0];
	return (1);
}
// Equation of sphere:
// dist(p, sphere->center) = rayon^2
int	intersect_sphere(t_ray *ray, t_object *sphere, float *t)
{
	t_quad	quad;
	t_vec3	oc;
	const t_vec3	axis = sphere->axis;

	oc = sub_vec3(ray->o, sphere->t_m.p);
	quad = solve_quadratic(oc, ray->d, sphere->radius);
	if (quad.delta < 0.0f)
		return (0);
	else if (quad.t[0] < 0.001f && quad.t[1] < 0.0f)
		return (0);
	else if (quad.t[0] > 0.001f && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > 0.00f)
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

int intersect_cylinder2(t_ray *ray, t_object *cylinder, float *t)
{
	//t_vec3	center = sub_vec3(cylinder->pos, mult_vec3(cylinder->axis, cylinder->height/2));
	t_vec3 center = cylinder->pos;
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

int intersect_cylinderoldold(t_ray *ray, t_object *cyl, float *t)
{
    t_vec3 axis = normalize_vec3(cyl->axis);
    t_vec3 base = cy_center_to_base(*cyl); 
    t_vec3 oc = sub_vec3(ray->o, base);
    float mn[2], y[2];
    t_quad quad;

    // Project ray direction and origin onto the cylinder's axis
    mn[0] = dot_vec3(ray->d, axis);       // Projection de la direction du rayon sur l'axe
    mn[1] = dot_vec3(oc, axis);           // Projection de l'origine du rayon sur l'axe
    t_vec3 d_perp = sub_vec3(ray->d, mult_vec3(axis, mn[0]));
    t_vec3 o_perp = sub_vec3(oc, mult_vec3(axis, mn[1]));

    quad = solve_quadratic(o_perp, d_perp, cyl->radius);

    if (quad.delta < 0)
    	return 0;

    // Compute y-coordinates of intersection points along the cylinder's axis
    y[0] = mn[1] + quad.t[0] * mn[0];
    y[1] = mn[1] + quad.t[1] * mn[0];

    // Check if intersections are within the cylinder's height
    int valid0 = (y[0] >= 0 && y[0] <= cyl->height);
    int valid1 = (y[1] >= 0 && y[1] <= cyl->height);

    if (!valid0 && !valid1) 
    	return 0; // Intersections hors du cylindre

    // 2. Intersection avec les disques des bases
    float t_cap[2];
    int cap_hit = 0;

    // Base inférieure
    if (fabsf(mn[0]) > EPSILON) 
    {
        t_cap[0] = (-mn[1]) / mn[0]; // Intersection avec le plan z=0
        t_vec3 hit = add_vec3(ray->o, mult_vec3(ray->d, t_cap[0]));
        if (mag_vec3(sub_vec3(hit, base)) <= cyl->radius && t_cap[0] > 0)
            cap_hit = 1;
    }

    // Base supérieure
    if (fabsf(mn[0]) < EPSILON)
    {
        t_cap[1] = (cyl->height - mn[1]) / mn[0]; // Intersection avec le plan z=height
        t_vec3 hit = add_vec3(ray->o, mult_vec3(ray->d, t_cap[1]));
        t_vec3 top = add_vec3(base, mult_vec3(axis, cyl->height));
        if (mag_vec3(sub_vec3(hit, top)) <= cyl->radius && t_cap[1] > 0)
            if (!cap_hit || t_cap[1] < t_cap[0])
            	cap_hit = 2;
    }

    // Combine les intersections (tube + disques)
    float t_min = INFINITY;
    if (valid0 && quad.t[0] > EPSILON && quad.t[0] < t_min)
    	t_min = quad.t[0];
    if (valid1 && quad.t[1] > EPSILON && quad.t[1] < t_min)
    	t_min = quad.t[1];
    if (cap_hit == 1 && t_cap[0] > EPSILON && t_cap[0] < t_min)
    	t_min = t_cap[0];
    if (cap_hit == 2 && t_cap[1] > EPSILON && t_cap[1] < t_min)
    	t_min = t_cap[1];

    if (t_min == INFINITY)
    	return 0;
    *t = t_min;
    return 1;
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

