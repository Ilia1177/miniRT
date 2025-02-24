/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:01:53 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:42:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	int		i;
	int		dlen;

	if (!s)
		return (0);
	if ((s + ft_strlen(s)) > (s + start))
	{
		dlen = ft_strlen(s + start);
		if ((size_t)dlen > len)
			dlen = len;
	}
	else
		return ((char *)ft_calloc(1, sizeof (char)));
	dest = 0;
	dest = (char *)ft_calloc(dlen + 1, sizeof (char));
	if (!dest)
		return (0);
	i = -1;
	while (++i < dlen && s[i + start] != '\0')
		dest[i] = s[start + i];
	dest[i] = '\0';
	return (dest);
}
