/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_plane_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:55:46 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

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

	str = *line + 2 ;
	init_obj(&plane, PLANE);
	scene->status = str_to_vec4(&str, &plane.t_m.p, 1.0f);
	if (!scene->status)
		scene->status = str_to_vecdir(&str, &plane.t_m.k);
	if (!scene->status)
		scene->status = str_to_argb(&str, &plane.color, 0);
	if (!scene->status)
		scene->status = get_options(&str, &plane);
	if (!scene->status)
		scene->status = make_object(plane, &scene->objects);
	*line = str + skip_space(str);
	return (scene->status);
}
