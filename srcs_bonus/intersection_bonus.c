#include <miniRT_bonus.h>
void	print_painter(t_painter *painter)
{
	print_vec4(painter->ray.o, "painter ray o:");
	print_vec4(painter->ray.d, "painter ray d:");
	print_vec4(painter->ray.v, "painter ray v:");
	print_vec4(painter->ray.n, "painter ray n:");
}
//t_object	*closest_intersect(t_ray *ray, int shw, float *lim, t_object *obj)
t_object	*closest_intersect(t_painter *painter, int shadow, t_object *obj)
{
	t_object		*closest_obj;
	float			closest_t;
	float	  		curr_t;
	const float		*lim = painter->lim;
	t_ray			*ray;

	ray = &painter->ray;
	closest_t = INFINITY;
	curr_t = INFINITY;
	closest_obj = NULL;
	if (ray->v.w < 0.0f)
		printf("CLOSEST INTERECTION:\n");
	while (obj)
	{

		if (intersect_object(ray, obj, &curr_t))
		{
			if (shadow && curr_t >= lim[0] && curr_t < lim[1])
				return (obj);
			if (curr_t < closest_t && curr_t >= lim[0] && curr_t < lim[1])
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
		//closest_obj->t = closest_t;
		painter->t = closest_t;
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
	t_ray			local_ray;
	int				intersect;
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
