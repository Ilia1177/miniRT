/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_applyalpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:43 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:45 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

t_argb	argb_applyalpha(t_argb color)
{
	const float	brightness = (float)color.a / 255;
	t_argb		real_color;

	real_color.a = 255;
	real_color.r = color.r * brightness;
	real_color.g = color.g * brightness;
	real_color.b = color.b * brightness;
	return (real_color);
}
