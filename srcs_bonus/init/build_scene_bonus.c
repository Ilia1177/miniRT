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

#include <minirt_bonus.h>

static void	choose_object(char **curr_line, t_data *scene)
{
	char	*line;

	line = *curr_line;
	if (!ft_strncmp("sp", line, 2))
		scene->status = create_sphere(&line, scene);
	else if (!ft_strncmp("pl", line, 2))
		scene->status = create_plane(&line, scene);
	else if (!ft_strncmp("cy", line, 2))
		scene->status = create_cylinder(&line, scene);
	else if (!ft_strncmp("hy", line, 2))
		scene->status = create_hyperboloid(&line, scene);
	else if (!ft_strncmp("tr", line, 2))
		scene->status = create_triangle(&line, scene);
	*curr_line = line;
	//printf("each line:%d\n", *line);
}

/*****************************************************************************
*	choose the good elem 
*	if is not a elem or newline print_error_mlx
*****************************************************************************/
static int	register_line_into_scene(char *line, t_data *scene)
{
	line += skip_space(line);
 
	while (line && *line && !scene->status)
	{
		//printf("while-line:%s\n", line);
		if (*line == '#')
			line += go_to_endl(line);
		choose_object(&line, scene);
		if (*line == 'A')
			scene->status = create_light(&line, scene, AMBIENT);
		else if (*line == 'L')
			scene->status = create_light(&line, scene, POINT);
		else if (*line == 'C')
			scene->status = place_camera(&line, scene);
		else if (*line && ft_strcmp("\n", line))
			scene->status = -4;
		else
			return (0);
	}
	if (scene->status)
		printf("Error\nOn line: %s\n", line);
	return (scene->status);
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
	gnl_clear_buffer(map);
	close(map);
	if (!scene->status)
		print_all(scene);
	return (scene->status);
}
