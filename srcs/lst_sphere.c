#include <miniRT.h>

static int	make_sphere(t_object data, t_object **objects)
{
	t_object	*curr_sphere;
	t_object	*new_sphere;

	new_sphere = malloc(sizeof(t_object));
	if (!new_sphere)
		return (-109);
	ft_memcpy(new_sphere, &data, sizeof(t_object));
	new_sphere->next = NULL;
	curr_sphere = NULL;
	if (*objects == NULL)
		*objects = new_sphere;
	else
	{
		curr_sphere = *objects;
		while (curr_sphere->next)
			curr_sphere = curr_sphere->next;
		curr_sphere->next = new_sphere;
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
	t_rgb		color;

	(void)scene;
	str = *line + 2 ;
	clean_obj(&sphere, SPHERE);
	status = str_to_vec3(&str, &sphere.pos);
	if (status != 0)
		return (status);
	status = str_to_float(&str, &sphere.radius);
	if (status != 0)
		return (status);
	status = str_to_rgb(&str, &color);
	if (status != 0)
		return (status);
	sphere.color = extract_argb(encode_rgb(color.r, color.g, color.b));
	*line = str + skip_space(str);
	if (make_sphere(sphere, &scene->objects) == -109)
		return (-109);
	return (0);
}
