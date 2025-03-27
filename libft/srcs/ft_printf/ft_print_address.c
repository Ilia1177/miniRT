/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:52:17 by npolack           #+#    #+#             */
/*   Updated: 2025/03/27 14:22:25 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	ft_put_address(int fd, unsigned long num, char *base)
{
	unsigned char	c;
	unsigned long	baselen;

	baselen = ft_strlen(base);
	if (num >= baselen)
		ft_put_address(fd, num / baselen, base);
	c = base[num % baselen];
	write(fd, &c, 1);
}

static int	get_intlen_address(unsigned long num, unsigned long baselen)
{
	int			len;

	len = 1;
	while (num >= baselen)
	{
		len++;
		num = num / baselen;
	}
	return (len);
}

int	ft_print_address(int fd, unsigned long n)
{
	int	len;

	if (n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	len = get_intlen_address(n, 16);
	len += ft_print_str(fd, "0x");
	ft_put_address(fd, n, "0123456789abcdef");
	return (len);
}
