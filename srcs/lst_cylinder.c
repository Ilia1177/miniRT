
#include <miniRT.h>

static int	make_cylinder(t_object data, t_object **objects)
{
	t_object	*curr_cylinder;
	t_object	*new_cylinder;

	new_cylinder = malloc(sizeof(t_object));
	if (!new_cylinder)
		return (-109);
	ft_memcpy(new_cylinder, &data, sizeof(t_object));
	new_cylinder->next = NULL;
	curr_cylinder = NULL;
	if (*objects == NULL)
		*objects = new_cylinder;
	else
	{
		curr_cylinder = *objects;
		while (curr_cylinder->next)
			curr_cylinder = curr_cylinder->next;
		curr_cylinder->next = new_cylinder;
	}
	return (0);
}

/*****************************************************************************
*  Check if the map file corresponding to the correct format
*  cylinder is sp		0.0,0.0,0.0		1.0			10,20,255
*					pos				radius		rgb
*	@param scene is the golbal data var
*	@param line is a str of the map file
*
*	return 0 on success or a error code
*****************************************************************************/
int	create_cylinder(char **line, t_data *scene)
{
	char		*str;
	t_object	cylinder;
	int			status;
	t_rgb		color;

	str = *line + 2 ;
	clean_obj(&cylinder, CYLINDER);
	status = str_to_vec3(&str, &cylinder.pos);
	if (status != 0)
		return (status);
	status = str_to_vecdir(&str, &cylinder.orientation);
	if (status != 0)
		return (status);
	status = str_to_float(&str, &cylinder.radius);
	if (status != 0)
		return (status);
	status = str_to_float(&str, &cylinder.height);
	if (status != 0)
		return (status);
	status = str_to_rgb(&str, &color);
	if (status != 0)
		return (status);
	cylinder.color = extract_argb(encode_rgb(color.r, color.g, color.b));
	*line = str + skip_space(str);
	return (make_cylinder(cylinder, &scene->objects));
}
