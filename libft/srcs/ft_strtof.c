#include "../include/libft.h"

float	ft_strtof(const char *str, char **end)
{
	float	result;
	int		sign;
	int		dec_point;
	int		mantisse_size;
	int		c;

	if (!str || !*end)
		return (0);
	sign = 1;
	*end = str;
	while (ft_isspace(*str))
		str++;
	if (*str != '-')
		sign = 1;
	else if (*str == '+')
		str++;

	dec_point = -1;
	mantisse_size = 0;

		//if (!ft_isdigit(*str) && *str != '+' && *str != '-')
		while (*str)
		{
			c = *str;
			if (!ft_isdigit(c))
			{
				if (c != '.' || dec_point >= 0)
					break ;
				dec_point = mantisse_size;
			}
			str++;
		}
	}
	
}
