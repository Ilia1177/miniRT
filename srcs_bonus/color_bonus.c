/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:51 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 12:44:08 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

void	limit_color(t_argb *color)
{
	color->a = fmin(255, fmax(0, color->a));
	color->r = fmin(255, fmax(0, color->r));
	color->g = fmin(255, fmax(0, color->g));
	color->b = fmin(255, fmax(0, color->b));
}

uint32_t	encode_argb(t_argb color)
{
	const uint32_t	alpha = color.a;
	const uint32_t	red = color.r;
	const uint32_t	green = color.g;
	const uint32_t	blue = color.b;

	return (alpha << 24 | red << 16 | green << 8 | blue);
}

t_argb	ease_color(t_argb color, uint8_t ease)
{
	t_argb	result;

	result.a = ease - color.a;
	result.r = ease - color.r;
	result.g = ease - color.g;
	result.b = ease - color.b;
	limit_color(&result);
	return (color);
}

t_argb	mult_colors(t_argb color, t_argb factor)
{
	t_argb	result;

	result.a = color.a * (factor.a / 255.0);
	result.r = color.r * (factor.r / 255.0);
	result.g = color.g * (factor.g / 255.0);
	result.b = color.b * (factor.b / 255.0);
	limit_color(&result);
	return (result);
}

t_argb	add_colors(t_argb color1, t_argb color2)
{
	t_argb			result;

	result.a = color1.a + color2.a;
	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	limit_color(&result);
	return (result);
}
