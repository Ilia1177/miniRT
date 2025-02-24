/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:36:45 by npolack           #+#    #+#             */
/*   Updated: 2024/10/16 19:16:18 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*found;

	found = 0;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			found = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	if (found)
		return (found);
	return (0);
}
