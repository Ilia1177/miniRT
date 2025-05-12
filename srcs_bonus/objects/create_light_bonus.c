/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_light_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:55:36 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:55:40 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
			curr_light = curr_light->next;
		curr_light->next = new_light;
	}
	return (0);
}

int	clean_lights(t_data *scene) // ???
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

	str = *line + 1 ;
	ft_bzero(&light, sizeof(light));
	light.type = type;
	if (type == POINT)
		scene->status = str_to_vec4(&str, &light.pos, 1.0f);
	if (!scene->status)
		scene->status = str_to_argb(&str, &light.intensity, 1);
	if (!scene->status)
	{
		str = str + skip_space(str);
		if (ft_strnstr(str, "-d", ft_strlen(str)))
		{
			light.type = DIRECTIONAL;
			light.pos.w = 0.0f;
			str += 2;
		}
		*line = str + skip_space(str);
		scene->status = make_light(light, &scene->lights);
	}
	return (scene->status);
}
