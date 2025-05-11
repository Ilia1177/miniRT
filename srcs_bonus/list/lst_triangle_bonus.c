/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_triangle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:56:02 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:56:04 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	create_triangle(char **line, t_data *scene)
{
	char		*str;
	t_object	triangle;
	int			status;

	str = *line + 2 ;
	init_obj(&triangle, TRIANGLE);
	status = str_to_vec4(&str, &triangle.vertice[0], 1.0f);
	if (!status)
		status = str_to_vec4(&str, &triangle.vertice[1], 1.0f);
	if (!status)
		status = str_to_vec4(&str, &triangle.vertice[2], 1.0f);
	if (!status)
		status = str_to_argb(&str, &triangle.color, 0);
	if (!status)
		status = get_options(&str, &triangle);
	if (triangle.path)
		triangle.img = new_img(scene, triangle.path);
	if (triangle.path && !triangle.img)
		return (-9);
	if (!status)
		status = make_object(triangle, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
