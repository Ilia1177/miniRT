#include "../include/libft.h"

float	ft_strtof(char *str, char **end)
{
	float	result;
	float	fraction;
	int		sign;
	int		i;
	if (!str || !*end)
		return (0);
	result = 0.0f;
	fraction = 1.0f;
	sign = 1;
	*end = str;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	else if (*str == '+')
		str++;
	i = -1;
	while (ft_isdigit(str[++i]))
		result = result * 10.0f + (str[i] - '0');
	if (*end == str || (i == 0 && *(--end)i)) 
		return (result);
	else if (str[i] == '.')
	{
		while(ft_isdigit(str[++i]))
		{
            fraction *= 0.1f;
            result += (str[i] - '0') * fraction;
		}
	}
	*end = str + i;
	return (result * sign);
}
