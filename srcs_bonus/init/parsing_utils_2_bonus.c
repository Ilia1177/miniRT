/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:46 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 11:36:18 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	check_nb_obj(t_data *scene)
{
	int			nb_sphere;
	int			nb_plane;
	int			nb_cylinder;
	t_object	*curr_obj;

	nb_sphere = 0;
	nb_cylinder = 0;
	nb_plane = 0;
	curr_obj = scene->objects;
	while (curr_obj)
	{
		if (curr_obj->type == SPHERE)
			nb_sphere++;
		if (curr_obj->type == CYLINDER)
			nb_cylinder++;
		if (curr_obj->type == PLANE)
			nb_plane++;
		curr_obj = curr_obj->next;
	}
	if (!nb_sphere || !nb_cylinder || !nb_plane)
		return (-6);
	return (0);
}

int	check_nb_light(t_data *scene)
{
	int			nb_ambient;
	int			nb_point;
	t_light		*curr_light;

	nb_ambient = 0;
	nb_point = 0;
	curr_light = scene->lights;
	while (curr_light)
	{
		if (curr_light->type == AMBIENT)
			nb_ambient++;
		if (curr_light->type == POINT)
			nb_point++;
		curr_light = curr_light->next;
	}
	if (nb_point != 1 || nb_ambient != 1)
		return (-7);
	return (0);
}

int	skip_space(char *str)
{
	int	space;

	space = 0;
	while (ft_isspace(str[space]))
		space++;
	return (space);
}

int	get_alpha(char **line, int *color, int alpha)
{
	char	*str;
	float	brightness;

	str = *line;
	if (alpha)
	{
		if (str_to_float(&str, &brightness))
			return (-2);
		*color = fmin(brightness, 1) * 255;
	}
	else
		*color = 255;
	str += skip_space(str);
	*line = str;
	return (0);
}

void	choose_options(char **line, t_object *obj, int *status)
{
	char	*str;

	str = *line;
	if (!ft_strncmp("-p", str, 2))
		*status = assign_opt(&str, &obj->pattern, 2);
	else if (!ft_strncmp("-spc", str, 4))
		*status = get_int_opt(&str, &obj->spec, 4);
	else if (!ft_strncmp("-opt", str, 2))
		*status = assign_opt(&str, &obj->opt, 4);
	else if (!ft_strncmp("-img", str, 4))
		*status = get_str_opt(&str, &obj->path, 4);
	else if (!ft_strncmp("-map", str, 4))
	{
		obj->normal_map = 1;
		*status = get_str_opt(&str, &obj->path, 4);
	}
	else if (!ft_strncmp("-ref", str, 4))
		*status = get_reflective(&str, &obj->reflect, 4);
	else if (ft_strcmp("\n", str))
		*status = -8;
	str += skip_space(str);
	*line = str;
}
