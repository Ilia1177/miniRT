/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:02:56 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:35:53 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*num_to_str(long int num, int len, int sign)
{
	int		i;
	char	*str;

	str = (char *)ft_calloc(len + 1, sizeof (char));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[len - i - 1] = (num % 10) + '0';
		num = num / 10;
		if (sign && len - i - 1 == 0)
			str[0] = '-';
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long int	num;
	int			sign;
	int			len;
	char		*str;

	num = n;
	sign = 0;
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	len = get_intlen(num, 10);
	if (num < 0)
	{
		num *= -1;
		sign = 1;
	}
	str = num_to_str(num, len, sign);
	if (!str)
		return (0);
	return (str);
}
