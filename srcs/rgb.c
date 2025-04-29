/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:23:46 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/29 18:26:11 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	encode_argb(t_argb color)
{
	const uint8_t	alpha = color.a;
	const uint8_t	red = color.r;
	const uint8_t	green = color.g;
	const uint8_t	blue = color.b;

	return (alpha << 24 | red << 16 | green << 8 | blue);
}

// do not use rgb, but argb instead (color.c) //
int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	encode_img_argb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

t_argb	extract_argb(int color)
{
	t_argb	argb_color;

	argb_color.a = (color >> 24) & 0xFF;
	argb_color.r = (color >> 16) & 0xFF;
	argb_color.g = (color >> 8) & 0xFF;
	argb_color.b = color & 0xFF;
	return (argb_color);
}

t_rgb	extract_rgb(int color)
{
	t_rgb	rgb_color;

	rgb_color.r = (color >> 16) & 0xFF;
	rgb_color.g = (color >> 8) & 0xFF;
	rgb_color.b = color & 0xFF;
	return (rgb_color);
}
