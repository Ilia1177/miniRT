#include <miniRT_bonus.h>

t_object	*closest_intersect(t_ray *ray, int shw, float t_min, float t_max, t_object *obj)
{
	t_object	*closest_obj;
	float		closest_t;
	float		curr_t;

	closest_t = t_max;
	curr_t = t_max;
	closest_obj = NULL;
	if (ray->v.w < 0.0f)
		printf("CLOSEST INTERECTION:\n");
	while (obj)
	{
		if (intersect_object(ray, obj, &curr_t))
		{
			if (shw && curr_t >= t_min && curr_t < t_max)
				return (obj);
			if (curr_t < closest_t && curr_t >= t_min && curr_t < t_max)
			{
				if (ray->v.w < 0.0f)
				{
					printf("Object hit: number: %d, curr_t: %f, closest_t: %f\n", (int)ray->v.w * -1, curr_t, closest_t);
					print_obj(*obj);
					ray->v.w -= 1.0f;
				}
				closest_t = curr_t;
				closest_obj = obj;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
	{
		closest_obj->t = closest_t;
		if (ray->v.w < 0.0f)
		{
			printf("Closest object: closest_t: %f, total object interecepted: %d\n", closest_t, ((int)ray->v.w * -1) - 1);
			print_obj(*closest_obj);
		}
	}
	return (closest_obj);
}

int	intersect_object(t_ray *ray, t_object *obj, float *t)
{
	t_ray	local_ray;
	int		intersect;
	const t_mat4	inv = mat_inverse(obj->t_m);
	intersect = 0;

	local_ray.d = mat_apply(inv, ray->d);
	local_ray.o = mat_apply(inv, ray->o);
	if (obj->type == SPHERE && intersect_sphere(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == CYLINDER && intersect_cylinder(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == PLANE && intersect_plane(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == HYPERBOL && intersect_hyperboloid(&local_ray, obj, t))
		intersect = 1;
	else if (obj->type == TRIANGLE && intersect_triangle(&local_ray, obj, t))
		intersect = 1;
	return (intersect);
}
