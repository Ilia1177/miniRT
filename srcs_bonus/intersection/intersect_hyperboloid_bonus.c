/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_hyperboloid_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:38:13 by npolack           #+#    #+#             */
/*   Updated: 2025/05/07 14:46:32 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// static void check_hyper_cap(float cap_z, t_vec4 o, t_vec4 d, t_vec4 s, float *t_min)
// {
//     float t;
//     float x, y, z;
//
//     if (fabsf(d.z) < EPSILON) // Ray parallel to cap plane
//         return;
//     t = (cap_z - o.z) / d.z;
//     if (t < EPSILON) // Ignore intersections behind/too close to ray
//         return;
//     // Calculate hit point coordinates
//     x = o.x + t * d.x;
//     y = o.y + t * d.y;
//     z = o.z + t * d.z;
//     // Verify z is within cap plane tolerance
//     if (fabsf(z - cap_z) > EPSILON)
//         return;
//     // Check if (x/s.x)^2 + (y/s.y)^2 <= 1 + (cap_z/s.z)^2 (hyperboloid equation at z=cap_z)
//     if ((x * x) / (s.x * s.x) + (y * y) / (s.y * s.y) <= 1.0f + (cap_z * cap_z) / (0.5 * 0.5) + EPSILON)
//     {
//         if (t < *t_min)
//             *t_min = t;
//     }
// }

int intersect_hyperboloid(t_ray *ray, t_object *hy, float *t)
{
	//const float		half_h = 0.5f;
	const t_vec4	o = ray->o;
	const t_vec4	d = ray->d;
	const t_vec4	s = hy->scale;
	t_quad			eq;

    eq.a = (d.x*d.x)/(s.x * s.x)
	   	+ (d.y*d.y)/(s.y * s.y) - (d.z*d.z)/(s.z * s.z);
    eq.b = 2.0f * ( (o.x*d.x)/(s.x * s.x)
		+ (o.y*d.y)/(s.y * s.y) - (o.z*d.z)/(s.z * s.z));
    eq.c = (o.x*o.x)/(s.x * s.x)
	   	+ (o.y*o.y)/(s.y * s.y) - (o.z*o.z)/(s.z * s.z) - 1.0f;
	if (!solve_quadratic(&eq))
		return (0);
//    if (eq.t[0] > EPSILON)
  //      *t = eq.t[0];
//    if (eq.t[1] > EPSILON && eq.t[1] < *t)
//        *t = eq.t[1];
    if (eq.t[0] > 0.001f)
		if (fabs(o.z + eq.t[0] * d.z) <= hy->height / 2.0f)
			*t = eq.t[0];
	if (eq.t[1] > 0.001f && eq.t[1] < *t)
		if (fabs(o.z + eq.t[1] * d.z) <= hy->height / 2.0f)
			*t = eq.t[1];
//	check_hyper_cap(-0.5f, o, d, s, t);
//	check_hyper_cap(0.5f, o, d, s, t);
	if (*t == T_MAX)
		return (0);
	return (1);
}
