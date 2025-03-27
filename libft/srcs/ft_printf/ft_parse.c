/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:07:17 by npolack           #+#    #+#             */
/*   Updated: 2025/03/27 14:17:40 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_parse(int fd, va_list args, const char *s)
{
	int	count_print;

	count_print = 0;
	if (*s == 'c')
		count_print = ft_print_char(fd, va_arg(args, int));
	else if (*s == 's')
		count_print = ft_print_str(fd, va_arg(args, char *));
	else if (*s == 'd' || *s == 'i')
		count_print = ft_print_dec(fd, va_arg(args, int));
	else if (*s == 'p')
		count_print = ft_print_address(fd, va_arg(args, unsigned long));
	else if (*s == 'u')
		count_print = ft_print_unsigned(fd, va_arg(args, unsigned int));
	else if (*s == 'x')
		count_print = ft_print_hex(fd, va_arg(args, int), 0);
	else if (*s == 'X')
		count_print = ft_print_hex(fd, va_arg(args, int), 1);
	else if (*s == 37)
		count_print = ft_print_char(fd, 37);
	else if (*--s)
		count_print = write(1, s--, 2);
	return (count_print);
}
