/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_checkerboard_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:01:42 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 13:35:00 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_board	checkerboard(t_argb color1, t_argb color2)
{
	t_board	tab;
	int		i;
	int		j;

	j = 0;
	while (j < CBOARD_H)
	{
		i = 0;
		while (i < CBOARD_W)
		{
			if ((i + j) % 2 == 0)
				tab.color[j][i] = color1;
			else
				tab.color[j][i] = color2;
			i++;
		}
		j++;
	}
	return (tab);
}

t_argb	checkerboard_at(float u, float v, t_argb obj_color)
{
	t_argb			color;
	const t_board	tab = checkerboard(obj_color, invert_color(obj_color));
	int				u2;
	int				v2;

	v2 = fmin(floor(v * CBOARD_H), CBOARD_H - 1);
	u2 = fmin(floor(u * CBOARD_W), CBOARD_H - 1);
	color = tab.color[v2][u2];
	return (color);
}

float clamp(float x, float min_val, float max_val) // doublons ///
{
    if (x < min_val) return min_val;
    if (x > max_val) return max_val;
    return x;
}

t_uv plane_map(t_vec4 local_point)
{
    t_uv uv;

    uv.u = fmodf(local_point.x, 1.0f);
    uv.v = fmodf(local_point.y, 1.0f);
    if (uv.u < EPSILON)
		uv.u += 1.0f;
    if (uv.v < EPSILON)
		uv.v += 1.0f;
    return uv;
}

// Convert to direction vector on unit sphere
// u: longitude (angle around Y axis), from -π to π
// v: latitude (angle from -Y to +Y), from -1 to 1
// acos(p.y) gives angle from Y axis in [0, π]
t_uv sphere_map(t_vec4 local_point)
{
    const t_vec4	p = normalize_vec4(local_point); 
    const float 	theta = atan2(p.z, p.x);
    const float		phi = acosf(clamp(p.y, -1.0f, 1.0f)); 
    t_uv			uv;

    uv.u = theta / (2.0f * M_PI);
    if (uv.u < 0.0f)
		uv.u += 1.0f;
    uv.v = phi / M_PI; 
    return uv;
}

t_uv cylinder_map(t_vec4 local_point)
{
    const float theta = atan2(local_point.x, local_point.y);
    t_uv		uv;

    uv.u = theta / (2.0f * M_PI);
    if (uv.u < EPSILON)
		uv.u += 1.0f;
    uv.v = local_point.z;
    uv.v = fmodf(uv.v, 1.0f);
    if (uv.v < EPSILON)
		uv.v += 1.0f;
    return uv;
}

/*****************************************************************************
 	* hp = hit point
******************************************************************************/
t_argb	pattern_color(t_ray *ray, t_object *obj)
{
	t_uv	uv;
	t_argb	color;
	t_vec4	hp;

	hp = mat_apply(mat_inverse(obj->t_m), ray->o);
	if (obj->type == SPHERE && obj->pattern)
		uv = sphere_map(hp);
	else if (obj->type == PLANE && obj->pattern)
		uv = plane_map(hp);
	else if (obj->type == CYLINDER && obj->pattern)
		uv = cylinder_map(hp);
	else
		return (obj->color);
	color = checkerboard_at(uv.u, uv.v, obj->color);
	return (color);
}
