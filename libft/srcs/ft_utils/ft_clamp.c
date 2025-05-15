/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:52 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 14:55:54 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

float	ft_clampf(float f, float min, float max)
{
	if (f > max)
		return (max);
	else if (f < min)
		return (min);
	return (f);
}

int	ft_clamp(int num, int min, int max)
{
	if (num > max)
		return (max);
	else if (num < min)
		return (min);
	return (num);
}
