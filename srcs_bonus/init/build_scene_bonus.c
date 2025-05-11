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

t_viewport	build_viewport(t_data *scene)
{
	const float	fov_radians = scene->cam.fov * (float)M_PI / 180.0f;
	t_viewport	vp;

	vp.proj = scene->viewport.proj;
	vp.w = 1.0f;
	vp.h = 1.0f;
	vp.pos.z = vp.w / (2.0f * tanf(fov_radians / 2.0f));
	vp.pos.x = 0.0f;
	vp.pos.y = 0.0f;
	return (vp);
}

t_type	typeof_projection(char **line)
{
	t_type	proj;

	printf("LINE: %s", *line);
	*line += skip_space(*line);
	printf("LINE: %s", *line);
	proj = PINHOLE;
	if (!ft_strncmp(*line, "-equ", 4))
		proj = EQUIRECT;
	else if (!ft_strncmp(*line, "-fis", 4))
		proj = FISHEYE;
	else if (!ft_strncmp(*line, "-ste", 4))
		proj = STEREO;
	if (proj != PINHOLE) 
		*line += 4;
	printf("LINE: %s", *line);
	printf("projection1 :: %d\n", proj);
	return (proj);
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
	scene->cam.t_m = mat_orthogonal(normalize_vec4(scene->cam.t_m.k)); //maybe not true ...
	scene->cam.t_m.p = pos;
	scene->status = str_to_float(&str, &f_fov);
	if (scene->status)
		return (scene->status);
	scene->cam.fov = (int)f_fov;
	*line = str + skip_space(str);
	scene->viewport.proj = typeof_projection(line);
	scene->viewport = build_viewport(scene);
	printf("projection1 :: %d\n", scene->viewport.proj);
	*line += skip_space(*line);
	return (scene->status);
}

void	choose_object(char **curr_line, t_data *scene)
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
	printf("each line:%d\n", *line);
}

/*****************************************************************************
*	choose the good elem 
*	if is not a elem or newline print_error_mlx
*****************************************************************************/
int	register_line_into_scene(char *line, t_data *scene)
{
	line += skip_space(line);
 
	while (line && *line && !scene->status)
	{
		printf("while-line:%s\n", line);
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
   if (!ft_strncmp(line, "equirectangular", 15))
    {
        scene->rect_proj = 1;
        free(line);
        line = get_next_line(map);
    }
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
