/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:43:21 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:44:02 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

t_argb	apply_brightness(t_argb color)
{
	const float	brightness = (float)color.a / 255;
	t_argb		real_color;

	real_color.a = 255;
	real_color.r = color.r * brightness;
	real_color.g = color.g * brightness;
	real_color.b = color.b * brightness;
	return (real_color);
}

t_argb	invert_color(t_argb color)
{
	t_argb	new_color;

	new_color.a = 255 - color.a;
	new_color.r = 255 - color.r;
	new_color.g = 255 - color.g;
	new_color.b = 255 - color.b;
	return (new_color);
}
