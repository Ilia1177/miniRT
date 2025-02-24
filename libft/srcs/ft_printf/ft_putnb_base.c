/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:36:13 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:44:14 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putnb_base(long long num, char *base)
{
	unsigned char	c;
	long long		baselen;

	if (num == LLONG_MIN)
	{
		write(1, "-9223372036854775808", 20);
		return ;
	}
	baselen = ft_strlen(base);
	if (num < 0)
	{
		num *= -1;
		write(1, "-", 1);
	}
	if (num >= baselen)
		ft_putnb_base(num / baselen, base);
	c = base[num % baselen];
	write(1, &c, 1);
}
