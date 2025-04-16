/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:24:26 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 11:24:27 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	make_light(t_light light, t_light **lights)
{
	t_light	*curr_light;
	t_light	*new_light;

	new_light = malloc(sizeof(t_light));
	if (!new_light)
		return (-109);
	ft_memcpy(new_light, &light, sizeof(t_light));
	new_light->next = NULL;
	if (*lights == NULL)
		*lights = new_light;
	else
	{
		curr_light = *lights;
		while (curr_light->next)
		{
			curr_light = curr_light->next;
			if (curr_light->type == new_light->type)
			{
				free(new_light);
				return (-5);
			}
		}
		curr_light->next = new_light;
	}
	return (0);
}

void	init_light(t_light *light, t_type type)
{
	light->type = type;
	light->pos = (t_vec4){0, 0, 0, 0};
	light->dir = (t_vec4){0, 0, 0, 0};
	light->intensity = (t_argb){0, 0, 0, 0};
	light->next = NULL;
}

int	clean_lights(t_data *scene)
{
	t_light	light;

	light = (t_light){NULL, (t_argb){20, 220, 220, 220},
		(t_vec4){-2, 0, 0, 0}, (t_vec4){1, 1, 0, 0}, DIRECTIONAL};
	if (make_light(light, &scene->lights) == -109)
		return (-109);
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
int	create_light(char **line, t_data *scene, t_type type)
{
	char		*str;
	t_light		light;
	int			status;

	str = *line + 1 ;
	init_light(&light, type);
	if (type == POINT)
	{
		status = str_to_vec3(&str, &light.pos);
		if (status != 0)
			return (status);
	}
	status = str_to_argb(&str, &light.intensity, 1);
	print_argb(light.intensity, "light");
	if (status != 0)
		return (status);
	*line = str + skip_space(str);
	return (make_light(light, &scene->lights));
}
