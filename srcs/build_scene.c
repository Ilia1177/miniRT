/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:59:39 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 16:47:23 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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

int	place_camera(char **line, t_data *scene)
{
	char	*str;
	int		status;
	float	f_fov;
	int		fov;

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
	status = str_to_float(&str, &f_fov);
	if (status != 0)
		return (status);
	fov = (int)f_fov;
	scene->cam.fov = fov;
	scene->viewport = build_viewport(scene, fov);
	*line = str + skip_space(str);
	return (status);
}

int	ambient_exist(t_data *scene)
{
	t_light	*light;

	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			return (1);
		light = light->next;
	}
	return (0);
}

/*****************************************************************************
*	choose the good elem 
*	if is not a elem or newline print_error_mlx
*****************************************************************************/
int	register_line_into_scene(char *line, t_data *scene, int status)
{
	line += skip_space(line);
	while (line && *line && !status)
	{
		if (*line == '#')
			line += go_to_endl(line);
		if (*line == 'A')
			status = create_light(&line, scene, AMBIENT);
		else if (*line == 'L')
			status = create_light(&line, scene, POINT);
		else if (*line == 'C')
			status = place_camera(&line, scene);
		else if (!ft_strncmp("sp", line, 2))
			status = create_sphere(&line, scene);
		else if (!ft_strncmp("pl", line, 2))
			status = create_plane(&line, scene);
		else if (!ft_strncmp("cy", line, 2))
			status = create_cylinder(&line, scene);
		else if (ft_strcmp("\n", line))
			status = -4;
		else
			return (0);
	}
	return (status);
}

int	check_map_elem(int status, t_data *scene)
{
	if (scene->cam.fov == -1 || scene->cam.fov > 180 || scene->cam.fov < 0)
		status = -10;
	if (status)
		print_error_msg(status, scene);
	status = check_nb_obj(scene);
	if (status)
		print_error_msg(status, scene);
	status = check_nb_light(scene);
	if (status)
		print_error_msg(status, scene);
	return (status);
}

int	build_scene(t_data *scene)
{
	char		*line;
	int			map;
	int			status;

	status = 0;
	map = open(scene->map_name, O_RDONLY);
	if (map == -1)
	{
		perror("miniRT: open_map");
		return (1);
	}
	line = get_next_line(map);
	while (!status && line)
	{
		status = register_line_into_scene(line, scene, status);
		free(line);
		line = get_next_line(map);
	}
	free(line);
	line = NULL;
	if (status)
		gnl_clear_buffer(map);
	close(map);
	status = check_map_elem(status, scene);
	return (status);
}
