/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:24:34 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 11:24:36 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	make_object(t_object data, t_object **objects)
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

	str = *line + 2 ;
	init_obj(&sphere, SPHERE);
	sphere.axis = (t_vec4){0, 0, 1, 0};
	status = str_to_vec3(&str, &sphere.pos);
	sphere.pos.w = 1;
	sphere.axis.w = 1;
	if (!status)
		status = str_to_float(&str, &sphere.radius);
	if (!status)
		status = str_to_argb(&str, &sphere.color, 0);
	if (!status)
		status = make_object(sphere, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
