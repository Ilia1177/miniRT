/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:57:53 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:57:55 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

float	clampf(float f, float min, float max)
{
	float	r_float;

	r_float = fminf(max, fmaxf(min, f));
	return (r_float);
}

void	clamp(int *num, int min, int max)
{
	if (*num < min)
		*num = min;
	if (*num > max)
		*num = max;
}
