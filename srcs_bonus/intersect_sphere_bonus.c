/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:55:38 by npolack           #+#    #+#             */
/*   Updated: 2025/04/10 14:55:50 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

// Equation of sphere:
// dist(p, sphere->center) = rayon^2
int	intersect_sphere(t_ray *ray, t_object *sp, float *t)
{
	t_quad			quad;
	const t_vec4	o = ray->o;
	const t_vec4	d = ray->d;
	const float 	r = sp->radius;

	quad.a = dot_vec3(d, d);
	quad.b = 2.0f * dot_vec3(o, d);
	quad.c = dot_vec3(o, o) - r * r;
	if (!solve_quadratic(&quad))
		return (0);
	else if (quad.t[0] < EPSILON && quad.t[1] < EPSILON)
		return (0);
	else if (quad.t[0] > EPSILON && quad.t[0] < quad.t[1])
		*t = quad.t[0];
	else if (quad.t[1] > EPSILON)
		*t = quad.t[1];
	return (1);
}
