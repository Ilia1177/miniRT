/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:10 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:55:13 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

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
	status = str_to_vec4(&str, &cylinder.t_m.p, 1.0f);
	if (!status)
		status = str_to_vecdir(&str, &cylinder.t_m.k);
	if (!status)
		status = str_to_float(&str, &cylinder.radius);
	if (!status)
		status = str_to_float(&str, &cylinder.height);
	if (!status)
		status = str_to_argb(&str, &cylinder.color, 0);
	if (!status)
		status = get_options(&str, &cylinder);
	if (!status)
		status = make_object(cylinder, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
