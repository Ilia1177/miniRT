/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sphere_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:49 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:55:51 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

	str = *line + 2 ;
	init_obj(&sphere, SPHERE);
	sphere.t_m.k = (t_vec4){0, 0, 1, 0};
	scene->status = str_to_vec4(&str, &sphere.t_m.p, 1.0f);
	if (!scene->status)
		scene->status = str_to_float(&str, &sphere.radius);
	if (!scene->status)
		scene->status = str_to_argb(&str, &sphere.color, 0);
	if (!scene->status)
		scene->status = get_options(&str, &sphere);
	if (sphere.path)
		sphere.img = new_img(scene, sphere.path);
	if (sphere.path && !sphere.img)
		return (-9);
	if (!scene->status)
		scene->status = make_object(sphere, &scene->objects);
	*line = str + skip_space(str);
	printf("create sphere");
	return (scene->status);
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
	if (plane.path)
		plane.img = new_img(scene, plane.path);
	if (plane.path && !plane.img)
		return (-9);
	if (!scene->status)
		scene->status = make_object(plane, &scene->objects);
	*line = str + skip_space(str);
	return (scene->status);
}

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

int	create_hyperboloid(char **line, t_data *scene)
{
	char		*str;
	t_object	hyperb;
	int			status;

	str = *line + 2 ;
	init_obj(&hyperb, HYPERBOL);
	status = str_to_vec4(&str, &hyperb.t_m.p, 1.0f);
	if (!status)
		status = str_to_vecdir(&str, &hyperb.t_m.k);
	if (!status)
		status = str_to_vec4(&str, &hyperb.scale, 2.0f);
	if (!status)
		status = str_to_float(&str, &hyperb.height);
	if (!status)
		status = str_to_argb(&str, &hyperb.color, 0);
	if (!status)
		status = get_options(&str, &hyperb);
	if (!status)
		status = make_object(hyperb, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
