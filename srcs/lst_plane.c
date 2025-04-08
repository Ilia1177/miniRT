#include <miniRT.h>

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

	str = *line + 2 ;
	init_obj(&plane, PLANE);
	status = str_to_vec3(&str, &plane.pos);
	if (status != 0)
		return (status);
	status = str_to_vecdir(&str, &plane.axis);
	if (status != 0)
		return (status);
	status = str_to_argb(&str, &plane.color, 0);
	if (status != 0)
		return (status);
	if (!status)
		status = make_object(plane, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
