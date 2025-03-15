/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:53:23 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/13 09:05:42 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	make_float(char *str, float *result, int *it)
{
	float	fraction;
	int		i;
	int		nb_frac_digit;

	i = *it;
	fraction = 1.0f;
	nb_frac_digit = 0;
	while (ft_isdigit(str[++i]))
		*result = (*result) * 10.0f + (str[i] - '0');
	if (str[i] == '.')
	{
		while (ft_isdigit(str[++i]))
		{
			nb_frac_digit++;
			*result = (*result) * 10.0f + (str[i] - '0');
		}
		if (nb_frac_digit)
		{
			while (nb_frac_digit--)
				fraction *= 10.0f;
			*result /= fraction;
		}
	}
	*it = i;
}

float	ft_strtof(char *str, char **end)
{
	float	result;
	int		sign;
	int		i;

	if (!str || !end)
		return (0);
	result = 0.0f;
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
	if (!ft_isdigit(*str) && !(*str == '.' && ft_isdigit(*(str + 1))))
		return (result);
	i = -1;
	make_float(str, &result, &i);
	*end = str + i;
	return (result * sign);
}
