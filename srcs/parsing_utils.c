#include <miniRT.h>

int	skip_space(char *str)
{
	int	space;

	space = 0;
	while (ft_isspace(str[space]))
		space++;
	return (space);
}

/*****************************************************************************
* convert a string to a vector 3
* @return int is code -1 for error or 1 for success
* 
* @param line is a pointer to the string
* @param v is a pointer to the vector to create
*
* 
*****************************************************************************/
int	str_to_vec4(char **line, t_vec4 *v)
{
	char	*str;
	char	*end;

	str = *line;
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

int	str_to_vecdir(char **line, t_vec4 *v)
{
	char	*str;
	char	*end;

	str = *line;
	v->x = (int)ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-2);
	norm_float(&v->x, -1.0f, 1.0f);
	str = end + 1;
	v->y = (int)ft_strtof(str, &end);
	if (*end != ',' || str == end)
		return (-2);
	norm_float(&v->y, -1.0f, 1.0f);
	str = end + 1;
	v->z = (int)ft_strtof(str, &end);
	if (str == end)
		return (-2);
	norm_float(&v->z, -1.0f, 1.0f);
	v->w = 0;
	*v = normalize_vec4(*v);
	*line = end;
	return (0);
}

int	get_int_opt(char **line, int *num, int nb_char)
{
	char	*str;
	char	*end;
	int		status;

	status = 0;
	str = *line + nb_char;
	end = str;
	*num = (int)ft_strtof(str, &end);
	if (!(str != end && ft_isspace(*end)))
		status = -8;
	*line = end;
	return (status);
}

int	get_str_opt(char **line, char **opt, int nb_char)
{
	char	*str;
	int		len;
	char	*new_str;

	str = *line + nb_char + 1;
	len = 0;
	while (str[len] && ft_strcmp("\n", &str[len]) && !ft_isspace(str[len]))
		len++;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (-109);
	ft_strlcpy(new_str, str, len + 1);
	*opt = new_str;
	*line = str + len;
	return (0);
}

int get_reflective(char **line, t_argb *c, int nb_char)
{
	char	*str;
	int		status;

	status = 0;
	str = *line + nb_char;
	status = str_to_argb(&str, c, 1);
	*line = str;
	return (status);
}

/*****************************************************************************
 	* Get (int)pattern (int)spec (t_argb)reflect of an object for bonus part
*****************************************************************************/
int	get_options(char **line, t_object *obj)
{
	char	*str;
	int		status;

	str = *line;
	str += skip_space(str);
	status = 0;
	while (str && *str && !status && ft_strcmp(str,"\n"))
	{
		if (!ft_strncmp("-p", str, 2))
			status = get_int_opt(&str, &obj->pattern, 2);
		else if (!ft_strncmp("-spc", str, 4))
			status = get_int_opt(&str, &obj->spec, 4);
		else if (!ft_strncmp("-o", str, 2))
			status = get_int_opt(&str, &obj->opt, 2);
		else if (!ft_strncmp("-img", str, 4))
			status = get_str_opt(&str, &obj->path, 4);
		else if (!ft_strncmp("-ref", str, 4))
			status = get_reflective(&str, &obj->reflect, 4);
		else if (ft_strcmp("\n", str))
			status = -8;
		str += skip_space(str);
    }
    *line = str;
    return (status);
}
