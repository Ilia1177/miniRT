
#include <miniRT_bonus.h>

//	static int	make_cylinder(t_object data, t_object **objects)
//	{
//		t_object	*curr_cylinder;
//		t_object	*new_cylinder;
//
//		new_cylinder = malloc(sizeof(t_object));
//		if (!new_cylinder)
//			return (-109);
//		ft_memcpy(new_cylinder, &data, sizeof(t_object));
//		new_cylinder->next = NULL;
//		curr_cylinder = NULL;
//		if (*objects == NULL)
//			*objects = new_cylinder;
//		else
//		{
//			curr_cylinder = *objects;
//			while (curr_cylinder->next)
//				curr_cylinder = curr_cylinder->next;
//			curr_cylinder->next = new_cylinder;
//		}
//		return (0);
//	}
//
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

	str = *line + 2 ;
	init_obj(&cylinder, CYLINDER);
	status = str_to_vec3(&str, &cylinder.pos);
	if (!status)
		status = str_to_vecdir(&str, &cylinder.axis);
	if (!status)
		status = str_to_float(&str, &cylinder.radius);
	if (!status)
		status = str_to_float(&str, &cylinder.height);
	if (!status)
		status = str_to_argb(&str, &cylinder.color, 0);
	if (!status)
	{
			cylinder.t_m = mat_generate(&cylinder);
			//inverse_matrix(cylinder.t_m, &cylinder.i_m);
	}
	if (!status)
		status = get_options(&str, &cylinder);
	if (!status)
		status = make_object(cylinder, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
