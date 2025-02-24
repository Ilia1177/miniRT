/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:36:47 by npolack           #+#    #+#             */
/*   Updated: 2024/10/30 12:40:30 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

int		ft_printf(const char *str, ...);
int		ft_parse(va_list args, const char *s);
int		ft_print_str(char *s);
int		ft_print_dec(int n);
int		ft_print_address(unsigned long n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, int maj);
int		ft_print_char(int c);
int		get_intlen(long long c, int baselen);
void	ft_putnb_base(long long num, char *base);

#endif
