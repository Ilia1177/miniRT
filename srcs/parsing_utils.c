#include <miniRT.h>

int	skip_space(char *str)
{
	int	space;

	space = 0;
	//printf("first char :%c, ascii: %d\n", str[space], str[space]);
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

/*****************************************************************************
* convert a string to a rgb
* @return int is code -1 for error or 1 for success
* 
* @param line is a pointer to the string
* @param v is a pointer to the vector to create
*
* 
*****************************************************************************/
int	str_to_rgb(char **line, t_rgb *c)
{
	char	*str;
	char	*end;

	str = *line;
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
	norm_rgb(c);
	*line = end;
	return (0);
}

int	str_to_radius(char **line, float *radius)
{
	char	*str;
	char	*end;

	str = *line;
	*radius = ft_strtof(str, &end);
	if (str == end)
		return (-3);
	*line = end;
	return (0);
}

void	norm_float(float *f, float min, float max)
{
	*f = fmin(max, fmin(min, *f));
}
