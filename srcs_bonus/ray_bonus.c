#include <miniRT_bonus.h>

void	r_reflect(t_ray *ray)
{
	const float	n_dot_d = dot_vec3(ray->n, ray->v);

	ray->d = mult_vec4(mult_vec4(ray->n, 2), n_dot_d);
	ray->d = normalize_vec4(sub_vec4(ray->d, ray->v));
}
// 1. Compute new origin of ray = hit point in world space
// 2. Get the vector to camera
// 3. Compute normal of object
void	r_update(t_ray *ray, t_object *obj)
{
	ray->o = add_vec4(mult_vec4(ray->d, obj->t), ray->o);
	ray->v = mult_vec4(ray->d, -1);
	if (obj->type == CYLINDER)
		cylinder_normal(ray, obj);
	else if (obj->type == SPHERE)
		sphere_normal(ray, obj);
	else if (obj->type == PLANE)
		plane_normal(ray, obj);
	else if (obj->type == TRIANGLE)
		triangle_normal(ray, obj);
	else
		hyperboloid_normal(ray, obj);
	if (dot_vec3(ray->n, ray->v) < 0)
		ray->n = mult_vec4(ray->n, -1);	
}

/*******************************************************************************
* 1) find intersection between ray and object
* 1.2. Compute t (distance on the rat->d);
* 2) get the hitting point, and assign it to ray->origin
* 3) calcul the normal of the hitting point in ray->n
* 4) compute light at hitting point
* 5) return color if no reflective or recursive <= 0
* 6) reflect ray and throw new ray to get reflections
*******************************************************************************/
t_argb	throw_ray(t_ray *ray, float t_min, float t_max, int rec, t_data *scene)
{
	t_object	*obj;
	t_argb		reflected_color;
	t_argb		local_color;
	t_argb		lumen;

	(void)rec;
	local_color = (t_argb) {0, 0, 0, 0};
	obj = closest_intersect(ray, 0, t_min, t_max, scene->objects);
	if (obj == NULL)
		return (local_color);
	r_update(ray, obj);
	lumen = compute_lighting(ray, obj, scene);
	local_color = mult_colors(pattern_color(ray, obj, scene), lumen);
	if (rec <= 0 || obj->reflect.a <= 0)
		return (local_color);
	r_reflect(ray);
	reflected_color = throw_ray(ray, EPSILON, t_max, rec - 1, scene);
	local_color = mult_colors(local_color, ease_color(obj->reflect, 255));
	reflected_color = mult_colors(reflected_color, obj->reflect);
	return (add_colors(local_color, reflected_color));
}

int	solve_quadratic(t_quad *quad)
{
	float	square_root;

	quad->delta = quad->b * quad->b - 4.0f * quad->a * quad->c;
	if (quad->delta < 0.0f)
	{
		quad->t[0] = FLT_MAX;
		quad->t[1] = FLT_MAX;
		return (0);
	}
	square_root = sqrtf(quad->delta);
	quad->t[0] = (-quad->b - square_root) / (2.0f * quad->a);
	quad->t[1] = (-quad->b + square_root) / (2.0f * quad->a);
	return (1);
}

