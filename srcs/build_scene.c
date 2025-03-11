#include <miniRT.h>

int	clear_gnl_buffer(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = free(line);
	}
}

int	skip_space(char *str)
{
	int space;

	space = 0;
	while (ft_isspace(str[space]))
		space++;
	return (space)
}

// write_coordinate
int	write_coordinate(char **line, t_vec3 *coords)
{
	char	*str;

	str = *line;
	str += skip_space(str);
	coords->x = ft_strtof(str, &end);
	if (*end != ',')
		return (5);
	coords->y = ft_strtof(++end, &end);
	if (*end != ',')
		return (5);
	coords->z = ft_strtof(++end, &end);
	*line = end;
	return (0);
}

// ft_strtof
// create_plane
// create_cylinder

// create_sphere
int create_sphere(char **line, t_data *scene)
{
	char		*str;
	t_sphere	sphere;
	int			status;

	str = *line;
	status = write_coordinate(&str, &sphere.pos);
	if (!status)
		sphere->radius = ft_strtof(str, &end);
	sphere->specular = 500;
	sphere->reflective = 0.3;
	sphere->color = get_color(str);
	make_sphere(sphere, scene);
	return (0);
}

// place_camera
int	place_camera(char **line, t_data *scene)
{
	char *str;
	int		status;

	str = *line;
	++str += skip_space(str);
	status = write_coordinate(&str, &scene->cam.pos);
	///scene->cam.yaw = 80.0f;
	//scene->cam.pitch = 0.0f;
	if (!status)
	{
		//status = write_coordinate(&str, &scene->cam.dir);
		printf("3D normalized orientation vector, in range [-1,1] for each x, y, z axis:\n");
	}
	if (!status)
	{
		printf("FOV\n");
	}
	return (status);
}

int	make_light(t_light light, t_data *scene)
{
	t_light *new_light;

	light = scene->light;
	while (new_light)
		new_light = new_light->next
	new_light = malloc(sizeof(t_light));
	if (!new_light)
		return (-1);
	new_light->intensity = light->intensity;
	new_light->pos = light->pos;
	//light->dir = dir;
	//light->color = color;
	return (0);
}

int	create_light(t_type type, char **line, t_data *scene)
{
	char	*str;
	char	*end;
	int		status;
	t_light	light;

	if (type == AMBIENT)
	{
		light = &scene->light;
		while (light)
		{
			if (light->type == AMBIENT)
				return (4);
			light = light->next;
		}
	}
	status = 0;
	str = *line;
	str += skip_space(str);
	if (!ft_isdigit(*str))
		return (2);
	else if (type == POINT)
		status = write_coordinate(&str, &light.pos);
	if (!status)
		light->intensity = ft_strtof(str, &end);
	if (!status && (light->intensity > 1.0f || light->intensity < 0.0f))
		return (3);
	if (make_light(light, scene) == -1)
		return (-1);
	*line = &end;
	return (status);
}

int	register_line_into_scene(char *line, t_data *scene)
{
	int	status;

	status = 0;
	line += skip_space(str);
	while (*line && !status)
	{
		if (*line == 'A')
			status = create_light(AMBIENT, &line, scene);
		else if (*line == 'L')
			status = create_light(POINT, &line, scene);
		else if (*line == 'C')
			status = place_camera(&line, scene);
		else if (!ft_strncmp("sp", line, 2))
			status = create_sphere(&line, scene);
		else if (!ft_strncmp("pl", line, 2))
			status = create_plane(&line, scene);
		else if (!ft_strncmp("cy", line, 2))
			status = create_cylinder(&line, scene);
		else
			return (1);
	}
	return (status);
}

int	build_scene(t_data *scene)
{
	char *line;
	int	map;
	int	status;

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
		status = register_line_into_scene(line, scene);
		free(line);
		line = get_next_line(map);
	}
	if (status)
		clear_gnl_buffer(map);
	return (status);
}



