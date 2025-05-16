/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:06:33 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 11:06:40 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_uv	plane_map(t_vec4 local_point)
{
	t_uv		uv;

	uv.u = fmodf(local_point.x, 1.0f);
	uv.v = fmodf(local_point.y, 1.0f);
	if (uv.u < EPSILON)
		uv.u += 1.0f;
	if (uv.v < EPSILON)
		uv.v += 1.0f;
	return (uv);
}

// Convert to direction vector on unit sphere
// u: longitude (angle around Y axis), from -π to π
// v: latitude (angle from -Y to +Y), from -1 to 1
// acos(p.y) gives angle from Y axis in [0, π]
t_uv	sphere_map(t_vec4 local_point)
{
	const t_vec4	p = normalize_vec4(local_point);
	const float		theta = atan2(p.z, p.x);
	const float		phi = acosf(ft_clampf(p.y, -1.0f, 1.0f));
	t_uv			uv;

	uv.u = 0.75f + theta / (2.0f * M_PI);
	uv.v = phi / M_PI;
	uv.u = fmodf(uv.u + 1.0f, 1.0f);
	uv.v = fminf(fmaxf(uv.v, 0.0f), 1.0f);
	return (uv);
}

t_uv	cylinder_map(t_vec4 local_point)
{
	const float	theta = atan2(local_point.x, local_point.y);
	t_uv		uv;

	uv.u = theta / (2.0f * M_PI);
	if (uv.u < EPSILON)
		uv.u += 1.0f;
	uv.v = local_point.z;
	uv.v = fmodf(uv.v, 1.0f);
	if (uv.v < EPSILON)
		uv.v += 1.0f;
	return (uv);
}

t_uv	get_uv(t_object *obj, t_vec4 hp)
{
	t_uv	uv;

	ft_bzero(&uv, sizeof(uv));
	if (obj->type == SPHERE)
		uv = sphere_map(hp);
	else if (obj->type == PLANE)
		uv = plane_map(hp);
	else if (obj->type == CYLINDER)
		uv = cylinder_map(hp);
	return (uv);
}
