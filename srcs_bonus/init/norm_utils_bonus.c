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

void	norm_float(float *f, float min, float max)
{
	*f = fmin(max, fmax(min, *f));
}

void	norm_int(int *num, int min, int max)
{
	*num = fmin(max, fmax(min, *num));
}
