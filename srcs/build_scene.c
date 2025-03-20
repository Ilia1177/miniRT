#include <miniRT.h>

void	clean_obj(t_object *obj, t_otype type)
{
	obj->type = type;
//	obj->t[0] = 0.0f;
//	obj->t[1] = 0.0f;
	obj->closest_t = 0.0f;
	obj->pos = (t_vec3){0, 0, 0};
	obj->orientation = (t_vec3){0, 0, 0};
	obj->spec = SPECULAR;
	obj->radius = 0.0f;
	obj->height = 0.0f;
	obj->reflect = (t_argb){0, 0, 0, 0};
	obj->color = (t_argb){0, 0, 0, 0};
	obj->next = NULL;
}

int	place_camera(char **line, t_data *scene)
{
	char	*str;
	int		status;
	float	f_fov;
	int		fov;

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
	print_cam(scene->cam);
	*line = str + skip_space(str);
	return (status);
}

int	register_line_into_scene(char *line, t_data *scene, int status)
{
	line += skip_space(line);
	while (line && *line && !status)
	{
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
	if (status < 0)
		print_error_msg(status);
	return (status);
}

int	build_scene(t_data *scene)
{
	char		*line;
	int			map;
	int			status;
	t_object	*it;
	t_light	*it2;

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
	{
		gnl_clear_buffer(map);
	}
	close(map);
	printf("**************************linked list OBJECT**************\n");
	it = scene->objects;
	while (it)
	{
		print_obj(*it);
		it = it->next;
	}
	printf("**************************linked list LIGHT**************\n");
	it2 = scene->lights;
	while (it2)
	{
		print_light(*it2);
		it2 = it2->next;
	}
	//return (1);
	return (status);
}
