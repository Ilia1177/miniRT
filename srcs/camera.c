/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:31:13 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 16:30:27 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Convert yaw & pitch to direction, right, and up vectors
// Compute new direction vector
// Compute right vector (always perpendicular to dir and world up)
// Compute up vector (perpendicular to dir and right)
void	update_camera_vectors(t_camera *cam)
{
	const float		rad_yaw = cam->yaw * (M_PI / 180.0f);
	const float		rad_pitch = cam->pitch * (M_PI / 180.0f);
	const t_vec4	world_up = {0, 1, 0, 0};

	cam->dir.x = cos(rad_yaw) * cos(rad_pitch);
	cam->dir.y = sin(rad_pitch);
	cam->dir.z = sin(rad_yaw) * cos(rad_pitch);
	cam->dir = normalize_vec4(cam->dir);
	cam->right = normalize_vec4(cross_vec4(world_up, cam->dir));
	cam->up = cross_vec4(cam->dir, cam->right);
}

t_vec4	apply_camera_rotation(t_camera cam, t_vec4 v)
{
	t_vec4	result;

	ft_bzero(&result, sizeof(result));
	result.x = cam.right.x * v.x + cam.up.x * v.y + cam.dir.x * v.z;
	result.y = cam.right.y * v.x + cam.up.y * v.y + cam.dir.y * v.z;
	result.z = cam.right.z * v.x + cam.up.z * v.y + cam.dir.z * v.z;
	return (result);
}

/******************************************************************************
 * calculate focal lenght from the fov
 * **************************************************************************/
t_viewport	build_viewport(t_data *scene, float fov_degrees)
{
	const float	fov_radians = fov_degrees * (float)M_PI / 180.0f;
	t_viewport	vp;

	vp = scene->viewport;
	vp.w = 1;
	vp.h = 1;
	vp.loc.z = vp.w / (2.0f * tanf(fov_radians / 2.0f));
	vp.loc.x = 0.0f;
	vp.loc.y = 0.0f;
	return (vp);
}

static void	yawpitch_from_dir(t_vec4 dir, float *yaw, float *pitch)
{
	dir = normalize_vec4(dir);
	*pitch = asinf(dir.y) * (180.0f / M_PI);
	*yaw = atan2f(dir.z, dir.x) * (180.0f / M_PI);
}

/******************************************************************************
* save the camera data in the general struct
* if cam.fov=-1 there is already a cam so generate an error
*******************************************************************************/
int	place_camera(char **line, t_data *scene)
{
	char	*str;
	int		status;
	float	f_fov;

	status = 0;
	if (scene->cam.fov != -1)
		status = -10;
	if (status != 0)
		return (status);
	str = *line + 1;
	status = str_to_vec3(&str, &scene->cam.pos);
	if (status != 0)
		return (status);
	status = str_to_vecdir(&str, &scene->cam.dir);
	if (status != 0)
		return (status);
	yawpitch_from_dir(scene->cam.dir, &scene->cam.yaw, &scene->cam.pitch);
	update_camera_vectors(&scene->cam);
	status = str_to_float(&str, &f_fov);
	if (status != 0)
		return (status);
	scene->cam.fov = (int)f_fov;
	scene->viewport = build_viewport(scene, (int)f_fov);
	*line = str + skip_space(str);
	return (status);
}
