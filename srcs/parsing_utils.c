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
int	str_to_vec3(char **line, t_vec3 *v)
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

int	str_to_vecdir(char **line, t_vec3 *v)
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
	*v = normalize_vec3(*v);
	*line = end;
	return (0);
}

