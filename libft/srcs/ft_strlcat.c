/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:12:38 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:42:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	if (size == 0)
		return (ft_strlen(src) + size);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	while (i < size - 1 && src[i - dst_len] != '\0')
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	dst[i] = '\0';
	if (size < dst_len)
		return (src_len + size);
	return (dst_len + src_len);
}
