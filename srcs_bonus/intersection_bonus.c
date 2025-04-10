#include <miniRT_bonus.h>

t_object	*closest_intersect(t_ray *ray, int shw, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;

	closest_t = t_max;
	curr_t = t_max;
	closest_obj = NULL;
	while (obj)
	{
		if (intersect_object(ray, obj, &curr_t))
		{
			if (shw && curr_t >= t_min && curr_t < t_max)
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

int	intersect_object(t_ray *ray, t_object *obj, float *t)
{
	t_ray	local_ray;
	int		intersect;

	intersect = 0;
	local_ray.d = normalize_vec4(mat_apply(obj->i_m, ray->d));
	local_ray.o = mat_apply(obj->i_m, ray->o);
	if (obj->type == SPHERE && intersect_sphere(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == CYLINDER && intersect_cylinder(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == PLANE && intersect_plane(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == HYPERBOL && intersect_hyperboloid(&local_ray, obj, t))
		intersect = 1;
	return (intersect);
}

int intersect_hyperboloid(t_ray *ray, t_object *object, float *t)
{
    // Extract hyperboloid parameters
    float a = object->scale.x;
    float b = object->scale.y;
    float c = object->scale.z;
    float radius = object->radius;
    float half_height = object->height * 0.5f;

    // Ray origin and direction in hyperboloid's local space
    float ox = ray->o.x;
    float oy = ray->o.y;
    float oz = ray->o.z;
    float dx = ray->d.x;
    float dy = ray->d.y;
    float dz = ray->d.z;

    // Precompute squared terms
    float a2 = a * a;
    float b2 = b * b;
    float c2 = c * c;
    float r2 = radius * radius;

    // Quadratic coefficients for (x²/a² + y²/b² - z²/c² = r²)
    float A = (dx*dx)/a2 + (dy*dy)/b2 - (dz*dz)/c2;
    float B = 2.0f * ((ox*dx)/a2 + (oy*dy)/b2 - (oz*dz)/c2);
    float C = (ox*ox)/a2 + (oy*oy)/b2 - (oz*oz)/c2 - r2;

    // Solve quadratic equation
    float discriminant = B*B - 4.0f*A*C;
    if (discriminant < 0)
        return 0;

    float sqrt_disc = sqrtf(discriminant);
    float t0 = (-B - sqrt_disc) / (2.0f * A);
    float t1 = (-B + sqrt_disc) / (2.0f * A);

    // Find valid intersections within height bounds
    float t_candidate = FLT_MAX;
    float z_hit;

    if (t0 > 0.001f) {
        z_hit = oz + t0 * dz;
        if (fabs(z_hit) <= half_height)
            t_candidate = t0;
    }
    if (t1 > 0.001f && t1 < t_candidate) {
        z_hit = oz + t1 * dz;
        if (fabs(z_hit) <= half_height)
            t_candidate = t1;
    }

    if (t_candidate == FLT_MAX)
        return 0;

    *t = t_candidate;
    return 1;
}
int intersect_hyperboloidi2(t_ray *ray, t_object *object, float *t)
{
    // 1. Compute the hyperboloid's axis (W) and total height h.
    t_vec4 W = normalize_vec4(object->t_m.k);

    float h = object->height;

    // 2. Compute the hyperboloid's center.
    // Here we assume object->pos is the top, so the center is halfway down the axis.
    t_vec4 center = sub_vec4(object->t_m.p, mult_vec4(W, h * 0.5f));

    // 3. Build an orthonormal basis (U, V, W).
    t_vec4 U;
    // Choose an arbitrary vector not parallel to W:
    if (fabs(W.x) > 0.001f || fabs(W.y) > 0.001f)
        U = normalize_vec4((t_vec4){ -W.y, W.x, 0, 0 });
    else
        U = normalize_vec4((t_vec4){ 0, 1, 0, 0});
    t_vec4 V = normalize_vec4(cross_vec4(W, U));

    // 4. Transform the ray into the hyperboloid's local space.
    // Compute oc = ray origin relative to center.
    t_vec4 oc = sub_vec4(ray->o, center);
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

