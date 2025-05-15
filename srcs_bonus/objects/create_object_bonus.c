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
	if (sphere.path && !scene->status)
		sphere.img = new_img(scene, sphere.path);
	if (!scene->status)
		scene->status = make_object(&sphere, scene);
	*line = str + skip_space(str);
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

	str = *line + 2 ;
	init_obj(&cylinder, CYLINDER);
	scene->status = str_to_vec4(&str, &cylinder.t_m.p, 1.0f);
	if (!scene->status)
		scene->status = str_to_vecdir(&str, &cylinder.t_m.k);
	if (!scene->status)
		scene->status = str_to_float(&str, &cylinder.radius);
	if (!scene->status)
		scene->status = str_to_float(&str, &cylinder.height);
	if (!scene->status)
		scene->status = str_to_argb(&str, &cylinder.color, 0);
	if (!scene->status)
		scene->status = get_options(&str, &cylinder);
	if (!scene->status)
		scene->status = make_object(&cylinder, scene);
	*line = str + skip_space(str);
	return (scene->status);
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
	if (!scene->status)
		scene->status = make_object(&plane, scene);
	*line = str + skip_space(str);
	return (scene->status);
}

int	create_triangle(char **line, t_data *scene)
{
	char		*str;
	t_object	triangle;

	str = *line + 2 ;
	init_obj(&triangle, TRIANGLE);
	scene->status = str_to_vec4(&str, &triangle.vertice[0], 1.0f);
	if (!scene->status)
		scene->status = str_to_vec4(&str, &triangle.vertice[1], 1.0f);
	if (!scene->status)
		scene->status = str_to_vec4(&str, &triangle.vertice[2], 1.0f);
	if (!scene->status)
		scene->status = str_to_argb(&str, &triangle.color, 0);
	if (!scene->status)
		scene->status = get_options(&str, &triangle);
	if (triangle.path)
		triangle.img = new_img(scene, triangle.path);
	if (!scene->status)
		scene->status = make_object(&triangle, scene);
	*line = str + skip_space(str);
	return (scene->status);
}

int	create_hyperboloid(char **line, t_data *scene)
{
	char		*str;
	t_object	hyperb;

	str = *line + 2 ;
	init_obj(&hyperb, HYPERBOL);
	scene->status = str_to_vec4(&str, &hyperb.t_m.p, 1.0f);
	if (!scene->status)
		scene->status = str_to_vecdir(&str, &hyperb.t_m.k);
	if (!scene->status)
		scene->status = str_to_vec4(&str, &hyperb.scale, 2.0f);
	if (!scene->status)
		scene->status = str_to_float(&str, &hyperb.height);
	if (!scene->status)
		scene->status = str_to_argb(&str, &hyperb.color, 0);
	if (!scene->status)
		scene->status = get_options(&str, &hyperb);
	if (!scene->status)
		scene->status = make_object(&hyperb, scene);
	*line = str + skip_space(str);
	return (scene->status);
}
