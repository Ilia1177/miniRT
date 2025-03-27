/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnb_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:36:13 by npolack           #+#    #+#             */
/*   Updated: 2025/03/27 14:21:32 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putnb_base(int fd, long long num, char *base)
{
	unsigned char	c;
	long long		baselen;

	if (num == LLONG_MIN)
	{
		write(fd, "-9223372036854775808", 20);
		return ;
	}
	baselen = ft_strlen(base);
	if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	if (num >= baselen)
		ft_putnb_base(fd, num / baselen, base);
	c = base[num % baselen];
	write(fd, &c, 1);
}
