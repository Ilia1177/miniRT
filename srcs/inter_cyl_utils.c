#include <miniRT.h>

int	min_pos(float *t, float t1, float t2)
{
	*t = fminf(t1, t2);
	if (*t < 0)
		return (0);
	return (1);
}

void get_min_t(float *t_min, float t_tmp, int *hit)
{
	*t_min = t_tmp;
	*hit = 1;
}

int check_height_cylinder(t_ray *ray, t_object *cy, float *t, t_quad quad)
{
	int				valid[2];
	const t_vec3	hit0 = add_vec3(ray->o, mult_vec3(ray->d, quad.t[0]));
	const t_vec3	hit1 = add_vec3(ray->o, mult_vec3(ray->d, quad.t[1]));
	const float		h0 = dot_vec3(sub_vec3(hit0, cy->pos), cy->axis);
	const float		h1 = dot_vec3(sub_vec3(hit1, cy->pos), cy->axis);

	valid[0] = (quad.t[0] > EPSILON) && (fabsf(h0) <= cy->height / 2);
	valid[1] = (quad.t[1] > EPSILON) && (fabsf(h1) <= cy->height / 2);
	if (valid[0] && valid[1])
		*t = fminf(quad.t[0], quad.t[1]);
	else if (valid[0])
		*t = quad.t[0];
	else if (valid[1])
		*t = quad.t[1];
	else
		return (0);
	return (1);
}

int	intersect_cylinder_lateral(t_ray *ray, t_object *cy, float *t)
{
	t_quad			quad;
	const t_vec3	oc = sub_vec3(ray->o, cy->pos);
	t_vec3			d_perp;
	t_vec3			oc_perp;

	d_perp = sub_vec3(ray->d, mult_vec3(cy->axis, dot_vec3(ray->d, cy->axis)));
	oc_perp = sub_vec3(oc, mult_vec3(cy->axis, dot_vec3(oc, cy->axis)));
	quad.a = dot_vec3(d_perp, d_perp);
	quad.b = 2.0f * dot_vec3(d_perp, oc_perp);
	quad.c = dot_vec3(oc_perp, oc_perp) - powf(cy->radius, 2);
	if (!solve_gen_quad(&quad) || (!min_pos(t, quad.t[0], quad.t[1])))
		return (0);
	if (!check_height_cylinder(ray, cy, t, quad))
		return (0);
	return (1);
}

int	intersect_disk(t_ray *ray, t_vec3 center, t_object *cyl, float *t)
{
	const float	denom = dot_vec3(cyl->axis, ray->d);
	float		temp;
	t_vec3		oc;
	t_vec3		hit;
	t_vec3		hit_vec;

	if (fabsf(denom) > EPSILON)
	{
		oc = sub_vec3(center, ray->o);
		temp = dot_vec3(oc, cyl->axis) / denom;
		if (temp > 0)
		{
			hit = add_vec3(ray->o, mult_vec3(ray->d, temp));
			hit_vec = sub_vec3(hit, center);
			if (dot_vec3(hit_vec, hit_vec) <= cyl->radius * cyl->radius)
			{
				*t = temp;
				return (1);
			}
		}
	}
	return (0);
}
