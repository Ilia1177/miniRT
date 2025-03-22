#include <miniRT.h>

static int	make_plane(t_object data, t_object **objects)
{
	t_object	*curr_plane;
	t_object	*new_plane;

	new_plane = malloc(sizeof(t_object));
	if (!new_plane)
		return (-109);
	ft_memcpy(new_plane, &data, sizeof(t_object));
	new_plane->next = NULL;
	curr_plane = NULL;
	if (*objects == NULL)
		*objects = new_plane;
	else
	{
		curr_plane = *objects;
		while (curr_plane->next)
			curr_plane = curr_plane->next;
		curr_plane->next = new_plane;
	}
	return (0);
}

/*****************************************************************************
*  Check if the map file corresponding to the correct format
*  plane is sp		0.0,0.0,0.0		1.0			10,20,255
*					pos				radius		rgb
*	@param scene is the golbal data var
*	@param line is a str of the map file
*
*	return 0 on success or a error code
*****************************************************************************/
int	create_plane(char **line, t_data *scene)
{
	char		*str;
	t_object	plane;
	int			status;
	t_rgb		color;

	str = *line + 2 ;
	clean_obj(&plane, PLANE);
	status = str_to_vec3(&str, &plane.pos);
	if (status != 0)
		return (status);
	status = str_to_vecdir(&str, &plane.axis);
	if (status != 0)
		return (status);
	status = str_to_rgb(&str, &color);
	if (status != 0)
		return (status);
	plane.color = extract_argb(encode_rgb(color.r, color.g, color.b));
	*line = str + skip_space(str);
	return (make_plane(plane, &scene->objects));
}
