/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:38:13 by npolack           #+#    #+#             */
/*   Updated: 2025/05/16 14:39:52 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//void	check_hyper_cap(float zc, t_vec4 o, t_vec4 d, t_vec4 s, float *t)
void	check_hyper_cap(float zc, t_ray *ray, t_vec4 s, float *t)
{
	const t_vec4		o = ray->o;
	const t_vec4		d = ray->d;
	float				t_cap;
	t_vec4				p;

	if (fabs(d.z) < EPSILON)
		return ;
	t_cap = (zc - o.z) / d.z;
	if (t_cap < EPSILON || t_cap >= *t)
		return ;
	p.x = o.x + t_cap * d.x;
	p.y = o.y + t_cap * d.y;
	if ((p.x * p.x) / (s.x * s.x) + (p.y * p.y) / (s.y * s.y) <= 1.0f)
		*t = t_cap;
}

int	intersect_hyperboloid(t_ray *ray, t_object *hy, float *t)
{
	const t_vec4	o = ray->o;
	const t_vec4	d = ray->d;
	const t_vec4	s = hy->scale;
	t_quad			eq;

	eq.a = (d.x * d.x) / (s.x * s.x)
		+ (d.y * d.y) / (s.y * s.y) - (d.z * d.z) / (s.z * s.z);
	eq.b = 2.0f * ((o.x * d.x) / (s.x * s.x)
			+ (o.y * d.y) / (s.y * s.y) - (o.z * d.z) / (s.z * s.z));
	eq.c = (o.x * o.x) / (s.x * s.x)
		+ (o.y * o.y) / (s.y * s.y) - (o.z * o.z) / (s.z * s.z) - 1.0f;
	if (!solve_quadratic(&eq))
		return (0);
	if (eq.t[0] > EPSILON)
		if (fabs(o.z + eq.t[0] * d.z) <= hy->height / 2.0f)
			*t = eq.t[0];
	if (eq.t[1] > EPSILON && eq.t[1] < *t)
		if (fabs(o.z + eq.t[1] * d.z) <= hy->height / 2.0f)
			*t = eq.t[1];
	check_hyper_cap(-(hy->height / 2), ray, s, t);
	check_hyper_cap(hy->height / 2, ray, s, t);
	if (*t == T_MAX)
		return (0);
	return (1);
}
