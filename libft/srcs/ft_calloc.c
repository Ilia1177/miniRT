/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:26:50 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:34:53 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	check;

	check = nmemb * size;
	array = 0;
	if (nmemb == 0 || size == 0)
	{
		array = malloc(0);
		if (!array)
			return (0);
		return (array);
	}
	if (nmemb > INT_MAX || size > INT_MAX)
		return (0);
	if (check > INT_MAX)
		return (0);
	array = malloc(nmemb * size);
	if (!array)
		return (0);
	ft_bzero(array, nmemb * size);
	return (array);
}
