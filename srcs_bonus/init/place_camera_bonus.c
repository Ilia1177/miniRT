/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_camera_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:58:39 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 10:58:49 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_type	typeof_projection(char **line)
{
	t_type	proj;

	*line += skip_space(*line);
	proj = PINHOLE;
	if (!ft_strncmp(*line, "-equ", 4))
		proj = EQUIRECT;
	else if (!ft_strncmp(*line, "-fis", 4))
		proj = FISHEYE;
	else if (!ft_strncmp(*line, "-ste", 4))
		proj = STEREO;
	if (proj != PINHOLE)
		*line += 4;
	return (proj);
}

static t_viewport	build_viewport(t_data *scene, char **line)
{
	const float	fov_radians = scene->cam.fov * (float)M_PI / 180.0f;
	t_viewport	vp;

	vp.proj = typeof_projection(line);
	vp.w = 1.0f;
	vp.h = 1.0f;
	vp.pos.z = vp.w / (2.0f * tanf(fov_radians / 2.0f));
	vp.pos.x = 0.0f;
	vp.pos.y = 0.0f;
	return (vp);
}

static void	yawpitch_from_dir(t_vec4 dir, float *yaw, float *pitch)
{
	dir = normalize_vec4(dir);
	*pitch = asinf(dir.y) * (180.0f / M_PI);
	*yaw = atan2f(dir.z, dir.x) * (180.0f / M_PI);
}

int	place_camera(char **line, t_data *scene)
{
	char	*str;
	float	f_fov;
	t_vec4	pos;

	if (scene->cam.fov != -1)
		return (32);
	str = *line + 1;
	scene->status = str_to_vec4(&str, &pos, 1.0f);
	if (scene->status)
		return (scene->status);
	scene->status = str_to_vecdir(&str, &scene->cam.t_m.k);
	if (scene->status)
		return (scene->status);
	scene->cam.t_m = mat_orthogonal(normalize_vec4(scene->cam.t_m.k));
	yawpitch_from_dir(scene->cam.t_m.k, &scene->cam.yaw, &scene->cam.pitch);
	update_camera_rotation(&scene->cam);
	scene->cam.t_m.p = pos;
	scene->status = str_to_float(&str, &f_fov);
	if (scene->status)
		return (scene->status);
	scene->cam.fov = (int)f_fov;
	*line = str + skip_space(str);
	scene->viewport = build_viewport(scene, line);
	*line += skip_space(*line);
	return (scene->status);
}
