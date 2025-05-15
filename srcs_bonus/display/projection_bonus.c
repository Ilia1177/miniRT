/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:27:03 by npolack           #+#    #+#             */
/*   Updated: 2025/05/13 15:27:06 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// Discard dirs outside circular fisheye bounds
// Angle from center
// Angle of the point in the image plane
// Spherical to Cartesian
// theta = r * fov
// phi = atan2f(y, x)
t_vec4 fisheye_proj(t_vec2 cnv, float fov)
{
	t_vec4		dir;
	const float	x = (((float)cnv.x + WIDTH / 2) / WIDTH * 2.0f) - 1.0f;
	const float	y = (((float)cnv.y + HEIGHT / 2) / HEIGHT * 2.0f) - 1.0f;
	const float	r = sqrtf(x * x + y * y);
	float		phi;

	fov = fov * (M_PI / 180.0f) / 2.0f;
	if (r > 1.0f)
	{
		dir = (t_vec4){0.0f, 0.0f, 0.0f, 0.0f};
		return (dir);
	}
	phi = atan2f(y, x);
	dir.x = sinf(r * fov) * cosf(phi);
	dir.y = sinf(r * fov) * sinf(phi);
	dir.z = cosf(r * fov);
	dir.w = 0.0f;
	return (dir);
}

t_vec4	stereographic_proj(t_vec2 cnv, t_viewport vp)
{
	(void)vp;
	t_vec4      dir;
	const float phi = (((float)cnv.x + WIDTH / 2) / WIDTH) * 2 * M_PI;
	const float theta = (((float)cnv.y + HEIGHT / 2) / HEIGHT) * M_PI;

	dir.x = sinf(theta) * cosf(phi);
	dir.y = cosf(theta);
	dir.z = sinf(theta) * sinf(phi);
	return (dir);
}

t_vec4	equirectangular_proj(t_vec2 cnv, t_viewport vp)
{
	(void)vp;
	t_vec4		dir;
	const float	phi = (((float)cnv.x + (float)WIDTH / 2) / (float)WIDTH) * 2 * M_PI;
	const float	theta = (1.0f - ((float)cnv.y + (float)HEIGHT / 2) / (float)HEIGHT) * M_PI;

	dir.x = sin(theta) * cos(phi);
	dir.y = cos(theta);
	dir.z = sin(theta) * sin(phi);
	return (dir);
}

// get location of the point in the viemport from canvas'location
t_vec4	pinhole_proj(t_vec2 cnv, t_viewport vp)
{
	t_vec4	dir;

	dir.x = (float)cnv.x * vp.w / WIDTH;
	dir.y = (float)cnv.y * vp.h / HEIGHT;
	dir.z = vp.pos.z;
	dir.w = 0.0f;
	dir = normalize_vec4(dir);
	return (dir);
}

t_vec4	projection(t_vec2 cnv, t_data *scene)
{
	t_vec4	dir;

	if (scene->viewport.proj == STEREO)
		dir = stereographic_proj(cnv, scene->viewport);
	else if (scene->viewport.proj == EQUIRECT)
		dir = equirectangular_proj(cnv, scene->viewport);
	else if (scene->viewport.proj == FISHEYE)
		dir = fisheye_proj(cnv, scene->cam.fov);
	else
		dir = pinhole_proj(cnv, scene->viewport);
	return (dir);
}
