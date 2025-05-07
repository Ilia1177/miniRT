/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:58:57 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:59:18 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

int	skip_space(char *str)
{
	int	space;

	space = 0;
	while (ft_isspace(str[space]))
		space++;
	return (space);
}

int	get_random_vec4(char **line, t_vec4 *v, float w)
{
	char	*str;
	float	mag;
	char	*end;

	str = *line;
	str += skip_space(str);
	if (!ft_strncmp(str, "ran", 3))
	{
		str += 3;
		end = str;
		mag = ft_strtof(str, &end);
		if (str == end)
			return (0);
		else
			*v = random_vec4(mag);
		v->w = w;
		*line = end;
		return (1);
	}
	return (0);
}

/*****************************************************************************
* convert a string to a vector 3 an assign w component
* if str = "   ran3.0   " -->  get a random vector of magnitude 3.0 
* @return int is code -1 for error or 1 for success
* 
* @param line is a pointer to the string
* @param v is a pointer to the vector to create
*
* 
*****************************************************************************/
int	str_to_vec4(char **line, t_vec4 *v, float w)
{
	char	*str;
	char	*end;

	str = *line;
	end = str;
	if (get_random_vec4(line, v, w))
		return (0);
	v->x = ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-1);
	str = end + 1;
	v->y = ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-1);
	str = end + 1;
	v->z = ft_strtof(str, &end);
	if (str == end)
		return (-1);
	v->w = w;
	*line = end;
	return (0);
}

int	get_alpha(char **line, int *color, int alpha)
{
	char	*str;
	char	*end;
	float	brightness;

	str = *line;
	end = str;
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

/*****************************************************************************
* convert a string to a rgb
* @return int is code -1 for error or 1 for success
* 
* @param line is a pointer to the string
* @param v is a pointer to the vector to create
* @param alpha is for 
* 
*****************************************************************************/
int	str_to_argb(char **line, t_argb *c, int alpha)
{
	char	*str;
	char	*end;

	str = *line;
	end = str;
	if (get_alpha(&str, &c->a, alpha))
		return (-2);
	c->r = (int)ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-2);
	str = end + 1;
	c->g = (int)ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-2);
	str = end + 1;
	c->b = (int)ft_strtof(str, &end);
	if (str == end)
		return (-2);
	limit_color(c);
	*line = end;
	return (0);
}

int	str_to_float(char **line, float *num)
{
	char	*str;
	char	*end;

	str = *line;
	*num = ft_strtof(str, &end);
	if (str == end)
		return (-3);
	*line = end;
	return (0);
}

/*****************************************************************************
 * return a normalized direction vector
 *****************************************************************************/
int	str_to_vecdir(char **line, t_vec4 *v)
{
	char	*str;
	char	*end;

	if (get_random_vec4(line, v, 0))
		return (0);
	str = *line;
	end = str;
	v->x = ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-2);
	norm_float(&v->x, -1.0f, 1.0f);
	str = end + 1;
	v->y = ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-2);
	norm_float(&v->y, -1.0f, 1.0f);
	str = end + 1;
	v->z = ft_strtof(str, &end);
	if (str == end)
		return (-2);
	norm_float(&v->z, -1.0f, 1.0f);
	v->w = 0;
	*v = normalize_vec4(*v);
	*line = end;
	return (0);
}
