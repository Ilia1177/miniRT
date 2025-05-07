/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_scene_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:38:05 by npolack           #+#    #+#             */
/*   Updated: 2025/05/05 15:52:35 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

int	place_camera(char **line, t_data *scene)
{
	char	*str;
	int		status;
	float	f_fov;
	int		fov;
	t_vec4	pos;

	if (scene->cam.fov != -1)
		return (32);
	str = *line + 1;
	status = str_to_vec4(&str, &pos, 1.0f);
	if (status != 0)
		return (status);
	status = str_to_vecdir(&str, &scene->cam.t_m.k);
	if (status != 0)
		return (status);
	scene->cam.t_m = mat_orthogonal(normalize_vec4(scene->cam.t_m.k));
	scene->cam.t_m.p = pos;
	status = str_to_float(&str, &f_fov);
	if (status != 0)
		return (status);
	fov = (int)f_fov;
	scene->cam.fov = fov;
	*line = str + skip_space(str);
	return (status);
}

int	register_line_into_scene(char *line, t_data *scene)
{
	line += skip_space(line);
	while (line && *line && !scene->status)
	{
		if (*line == '#')
			line += go_to_endl(line);
		if (*line == 'A')
			scene->status = create_light(&line, scene, AMBIENT);
		else if (*line == 'L')
			scene->status = create_light(&line, scene, POINT);
		else if (*line == 'C')
			scene->status = place_camera(&line, scene);
		else if (!ft_strncmp("sp", line, 2))
			scene->status = create_sphere(&line, scene);
		else if (!ft_strncmp("pl", line, 2))
			scene->status = create_plane(&line, scene);
		else if (!ft_strncmp("cy", line, 2))
			scene->status = create_cylinder(&line, scene);
		else if (!ft_strncmp("hy", line, 2))
			scene->status = create_hyperboloid(&line, scene);
		else if (!ft_strncmp("tr", line, 2))
			scene->status = create_triangle(&line, scene);
		else if (ft_strcmp("\n", line))
			scene->status = -4; // ???
		else
			return (0);
	}
	if (scene->status)
		printf("Error\nOn line: %s\n", line);
	return (scene->status);
}

int	check_map_elem(int status, t_data *scene)
{
	if (!status)
		print_all(scene);
	if (scene->cam.fov == -1)
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

	map = open(scene->map_name, O_RDONLY);
	if (map == -1)
	{
		perror("miniRT: open_map");
		return (30);
	}
	line = get_next_line(map);
	while (!scene->status && line)
	{
		scene->status = register_line_into_scene(line, scene);
		free(line);
		line = get_next_line(map);
	}
	free(line);
	//line = NULL;
	//if (status)
		gnl_clear_buffer(map);
	close(map);

	if (!scene->status)
		print_all(scene);
	//status = check_map_elem(status, scene);
	return (scene->status);
}
