/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:51:17 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:42:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		result;
	size_t	i;

	i = 0;
	result = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		result += ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (result != 0)
			return (result);
		i++;
	}
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		result += ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (result != 0)
			return (result);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
