/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:04:12 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:42:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	is_in_set(char *c, char const	*set)
{
	while (*set)
	{
		if ((unsigned char)*c == (unsigned char)*set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	char	*start;
	char	*end;

	if (s1 == 0 || set == 0)
		return (0);
	if (*s1 == '\0')
		return ((char *)ft_calloc(1, sizeof (char)));
	start = (char *)s1;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (*start && is_in_set(start, set))
		while (is_in_set(start, set))
			start++;
	while (end > s1 && is_in_set(end, set))
		while (is_in_set(end, set))
			end--;
	if (end - start + 1 <= 0)
		return ((char *)ft_calloc(1, sizeof (char)));
	dest = (char *)ft_calloc(end - start + 2, sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, start, end - start + 2);
	return (dest);
}
