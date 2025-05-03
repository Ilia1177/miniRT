/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:01:21 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/03 19:19:56 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	min_pos(float *t, float t1, float t2)
{
	*t = fminf(t1, t2);
	if (*t < 0)
		return (0);
	return (1);
}

void	get_min_t(float *t_min, float t_tmp, int *hit)
{
	if (*t_min > t_tmp)
	{
		*t_min = t_tmp;
		*hit = 1;
	}
}

int	check_height_cylinder(t_ray *ray, t_object *cy, float *t, t_quad quad)
{
	int				valid[2];
	const t_vec4	hit0 = add_vec4(ray->o, mult_vec4(ray->d, quad.t[0]));
	const t_vec4	hit1 = add_vec4(ray->o, mult_vec4(ray->d, quad.t[1]));
	const float		h0 = dot_vec4(sub_vec4(hit0, cy->pos), cy->axis);
	const float		h1 = dot_vec4(sub_vec4(hit1, cy->pos), cy->axis);

	valid[0] = (quad.t[0] > EPSILON) && (fabsf(h0) <= cy->height / 2.0f);
	valid[1] = (quad.t[1] > EPSILON) && (fabsf(h1) <= cy->height / 2.0f);
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
	const t_vec4	oc = sub_vec4(ray->o, cy->pos);
	t_vec4			d_perp;
	t_vec4			oc_perp;

	ft_bzero(&quad, sizeof(t_quad));
	d_perp = sub_vec4(ray->d, mult_vec4(cy->axis, dot_vec4(ray->d, cy->axis)));
	oc_perp = sub_vec4(oc, mult_vec4(cy->axis, dot_vec4(oc, cy->axis)));
	quad.a = dot_vec4(d_perp, d_perp);
	quad.b = 2.0f * dot_vec4(d_perp, oc_perp);
	quad.c = dot_vec4(oc_perp, oc_perp) - powf(cy->radius, 2);
	if (!solve_gen_quad(&quad) || (!min_pos(t, quad.t[0], quad.t[1])))
		return (0);
	if (!check_height_cylinder(ray, cy, t, quad))
		return (0);
	return (1);
}

int	intersect_disk(t_ray *ray, t_vec4 center, t_object *cyl, float *t)
{
	const float	denom = dot_vec4(cyl->axis, ray->d);
	float		temp;
	t_vec4		oc;
	t_vec4		hit;
	t_vec4		hit_vec;

	if (fabsf(denom) < FLT_EPSILON)
		return (0);
	oc = sub_vec4(center, ray->o);
	temp = dot_vec4(oc, cyl->axis) / denom;
	if (temp < EPSILON)
		return (0);
	hit = add_vec4(ray->o, mult_vec4(ray->d, temp));
	hit_vec = sub_vec4(hit, center);
	if (dot_vec4(hit_vec, hit_vec) <= (cyl->radius * cyl->radius * 1.01f))
	{
		*t = temp;
		return (1);
	}
	return (0);
}
