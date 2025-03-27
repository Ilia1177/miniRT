/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:47:39 by npolack           #+#    #+#             */
/*   Updated: 2025/03/27 14:18:58 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_print_unsigned(int fd, unsigned int n)
{
	int	len;

	len = get_intlen(n, 10);
	ft_putnb_base(fd, n, "0123456789");
	return (len);
}
