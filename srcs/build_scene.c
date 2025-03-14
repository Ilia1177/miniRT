#include <miniRT.h>


// ft_strtof
// create_plane
// create_cylinder
int	create_plane(char **line, t_data *scene)
{
	(void)line;
	(void)scene;
	printf("make plane\n");
	return (0);
}

int	create_cylinder(char **line, t_data *scene)
{
	(void)line;
	(void)scene;
	printf("make cylinder\n");
	return (0);
}

int	make_sphere(t_object data, t_object **objects)
{
	t_object	*curr_sphere;
	t_object	*new_sphere;

	new_sphere = malloc(sizeof(t_object));
	if (!new_sphere)
		return (-1);
	ft_memcpy(new_sphere, &data, sizeof(t_object));
	new_sphere->next = NULL;
	curr_sphere = NULL;
	if(*objects == NULL)
		*objects = new_sphere;
	else
	{
		curr_sphere = *objects;
		while (curr_sphere->next)
			curr_sphere = curr_sphere->next;
		curr_sphere->next = new_sphere;
	}
	print_obj(*new_sphere);
	return (0);
}

// create_sphere
int	create_sphere(char **line, t_data *scene)
{
	char		*str;
	t_object	sphere;
	int			status;
	t_rgb		color;

	(void)scene;
	str = *line + 2 ;
	sphere.type = SPHERE;
	status = str_to_vec3(&str, &sphere.pos);
	if (status != 0)
		return (status);
	status = str_to_radius(&str, &sphere.radius);
	if (status != 0)
		return (status);
	sphere.specular = SPECULAR;
	//sphere.reflective = REFLECTIVE; reflective is t_argb
	status = str_to_rgb(&str, &color);
	if (status != 0)
		return (status);
	//sphere.color = encode_rgb(color.r, color.g, color.b); // need Alpha chanel
	print_obj(sphere);
	*line = str;
	make_sphere(sphere, &scene->objects);
	return (0);
}

// place_camera
int	place_camera(char **line, t_data *scene)
{
	char *str;
	int		status;

	str = *line;
	str++;
	str += skip_space(str);
	status = str_to_vec3(&str, &scene->cam.pos);
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

	new_light = scene->lights;
	while (new_light)
		new_light = new_light->next;
	new_light = malloc(sizeof(t_light));
	if (!new_light)
		return (-1);
	new_light->intensity = light.intensity;
	new_light->pos = light.pos;
	//light->dir = dir;
	//light->color = color;
	return (0);
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

int	create_light(t_ltype type, char **line, t_data *scene)
{
	char	*str;
	char	*end;
	int		status;
	t_light	light;

	if (ambient_exist(scene))
		return (9);
	status = 0;
	str = *line;
	end = str;
	str += skip_space(str);
	if (!ft_isdigit(*str))
		return (2);
	else if (type == POINT)
		status = str_to_vec3(&str, &light.pos);
	if (!status)
		light.intensity.a = ft_strtof(str, &end);				//				intensity is t_argb
	if (!status && (light.intensity.a > 1.0f || light.intensity.a < 0.0f))	
		return (3);
	if (make_light(light, scene) == -1)
		return (-1);
	*line = end;
	return (status);
}

int	register_line_into_scene(char *line, t_data *scene)
{
	int	status;

	printf("register line\n");
	status = 0;
	line += skip_space(line);
	while (line && *line && !status)
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
			return (0);
	}
	printf("register line: status: %d\n", status);
	return (status);
}

int	build_scene(t_data *scene)
{
	char	*line;
	int		map;
	int		status;

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
		gnl_clear_buffer(map);
	printf("**************************linked list**************\n");
	while(scene->objects)
	{
		print_obj(*scene->objects);
		scene->objects = scene->objects->next;
	}
	return (status);
}
