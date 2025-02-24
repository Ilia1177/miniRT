/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:02:09 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:39:24 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int			i;
	char		*d;
	char		*s;

	if (!dest && !src)
		return (0);
	s = (char *)src;
	d = (char *)dest;
	i = 0;
	while (i < (int)n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dest);
}
