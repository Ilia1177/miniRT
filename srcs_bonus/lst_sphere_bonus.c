#include <miniRT_bonus.h>

static void	make_matrix(t_object data, t_object *new)
{
	const float	scale = data.radius;

	new->t_m = mat_orthogonal(data.t_m.k);
	new->t_m.p = data.t_m.p;
	if (data.type == SPHERE)
		mat_scale(&new->t_m, scale, scale, scale);
	else if (data.type == CYLINDER)
		mat_scale(&new->t_m, data.radius, data.radius, data.height);
	else if (data.type == PLANE)
		mat_scale(&new->t_m, 1, 1, 1);
	else if (data.type == HYPERBOL)
		mat_scale(&new->t_m, 1.0f, 1.0f, 1.0f);
	//	new->i_m = mat_scale(&new->t_m, data.scale.x, data.scale.y, data.scale.z);
	else if (data.type == TRIANGLE)
		new->t_m = mat_init_id();
}

int	make_object(t_object data, t_object **objects)
{
	t_object	*curr_object;
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (-109);
	ft_memcpy(new_object, &data, sizeof(t_object));
	make_matrix(data, new_object);
	new_object->next = NULL;
	curr_object = NULL;
	if (*objects == NULL)
		*objects = new_object;
	else
	{
		curr_object = *objects;
		while (curr_object->next)
			curr_object = curr_object->next;
		curr_object->next = new_object;
	}
	return (0);
}

/*****************************************************************************
*  Check if the map file corresponding to the correct format
*  SPHERE is sp		0.0,0.0,0.0		1.0			10,20,255
*					pos				radius		rgb
*	@param scene is the golbal data var
*	@param line is a str of the map file
*
*	return 0 on success or a error code
*****************************************************************************/
int	create_sphere(char **line, t_data *scene)
{
	char		*str;
	t_object	sphere;
	int			status;

	str = *line + 2 ;
	init_obj(&sphere, SPHERE);
	sphere.t_m.k = (t_vec4){0, 0, 1, 0};
	status = str_to_vec4(&str, &sphere.t_m.p, 1.0f);
	if (!status)
		status = str_to_float(&str, &sphere.radius);
	if (!status)
		status = str_to_argb(&str, &sphere.color, 0);
	if (!status)
		status = get_options(&str, &sphere);
	if (sphere.path)
		sphere.img = text_img(scene, sphere.path);
	if (sphere.path && !sphere.img)
		return (-9);
	if (!status)
		status = make_object(sphere, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
