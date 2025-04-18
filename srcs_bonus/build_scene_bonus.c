#include <miniRT_bonus.h>

int	check_nb_obj(t_data *scene)
{
	int			nb_sphere;
	int			nb_plane;
	int			nb_cylinder;
	t_object	*curr_obj;

	nb_sphere = 0;
	nb_cylinder = 0;
	nb_plane = 0;
	curr_obj = scene->objects;
	while (curr_obj)
	{
		if (curr_obj->type == SPHERE)
			nb_sphere++;
		if (curr_obj->type == CYLINDER)
			nb_cylinder++;
		if (curr_obj->type == PLANE)
			nb_plane++;
		curr_obj = curr_obj->next;
	}
	if (!nb_sphere || !nb_cylinder || !nb_plane)
		return (-6);
	return (0);
}

int	check_nb_light(t_data *scene)
{
	int			nb_ambient;
	int			nb_point;
	t_light	*curr_light;

	nb_ambient = 0;
	nb_point = 0;
	curr_light = scene->lights;
	while (curr_light)
	{
		if (curr_light->type == AMBIENT)
			nb_ambient++;
		if (curr_light->type == POINT)
			nb_point++;
		curr_light = curr_light->next;
	}
	if (!nb_point || !nb_ambient)
		return (-7);
	return (0);
}

void	init_obj(t_object *obj, t_type type)
{
	ft_bzero(obj, sizeof(t_object));
	obj->type		= type;
	obj->t_m		= mat_init_id();
	obj->spec		= SPECULAR;
}

int	place_camera(char **line, t_data *scene)
{
	char	*str;
	int		status;
	float	f_fov;
	int		fov;
	t_vec4	pos;

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
	//fov = (int)f_fov;
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

int	go_to_endl(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\n' && str[c])
		c++;
	return (c);
}

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
		else if (!ft_strncmp("hy", line, 2))
			status = create_hyperboloid(&line, scene);
		else if (!ft_strncmp("tr", line, 2))
			status = create_triangle(&line, scene);
		else if (ft_strcmp("\n", line))
			status = -4;
		else
			return (0);
	}
	print_error_msg(status, line);
	return (status);
}

void	print_all(t_data *scene)
{
	t_object	*obj;
	t_light		*light;

	printf("**************************linked list OBJECT**************\n");
	obj = scene->objects;
	while (obj)
	{
		print_obj(*obj);
		obj = obj->next;
	}
	printf("**************************linked list LIGHT**************\n");
	light = scene->lights;
	while (light)
	{
		print_light(*light);
		light = light->next;
	}
	printf("****************************CAMERA **********************\n");
	print_cam(scene->cam);
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
		return (2);
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
	if (!status)
		print_all(scene);
		//status = check_nb_obj(scene);
	//if (status)
	//	print_error_msg(status);
	//status = check_nb_light(scene);
	//if (status)
	//	print_error_msg(status);
	//return (1);
	return (status);
}
