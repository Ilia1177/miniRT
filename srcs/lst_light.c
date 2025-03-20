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

void	clean_light(t_light *light, t_ltype type)
{
	light->type = type;
	light->pos = (t_vec3){0, 0, 0};
	light->dir = (t_vec3){0, 0, 0};
	light->intensity = (t_argb){0, 0, 0, 0};
	light->next = NULL;
}

int	clean_lights(t_data *scene)
{
	t_light	light;

	light = (t_light){DIRECTIONAL, (t_argb){20, 220, 220, 220},
		(t_vec3){-2, 0, 0}, (t_vec3){0, 0, 0}, NULL};
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
int	create_light(char **line, t_data *scene, t_ltype type)
{
	char		*str;
	t_light		light;
	int			status;
	t_rgb		color;
	float		bright;

	str = *line + 1 ;
	clean_light(&light, type);
	if (type == POINT)
	{
		status = str_to_vec3(&str, &light.pos);
		if (status != 0)
			return (status);
	}
	status = str_to_float(&str, &bright);
	if (status != 0)
		return (status);
	norm_float(&bright, 0, 1);
	status = str_to_rgb(&str, &color);
	if (status != 0)
		return (status);
	light.intensity = extract_argb(encode_rgb(color.r, color.g, color.b));
	add_bright_argb(&light.intensity, bright);
	*line = str + skip_space(str);
	return (make_light(light, &scene->lights));
}
