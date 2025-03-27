/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:36:47 by npolack           #+#    #+#             */
/*   Updated: 2025/03/27 14:20:39 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

int		ft_dprintf(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);
int		ft_parse(int fd, va_list args, const char *s);
int		ft_print_str(int fd, char *s);
int		ft_print_dec(int fd, int n);
int		ft_print_address(int fd, unsigned long n);
int		ft_print_unsigned(int fd, unsigned int n);
int		ft_print_hex(int fd, unsigned int n, int maj);
int		ft_print_char(int fd, int c);
int		get_intlen(long long c, int baselen);
void	ft_putnb_base(int fd, long long num, char *base);

#endif
