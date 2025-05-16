/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_encode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:04 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:14:05 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

uint32_t	argb_toint(t_argb color)
{
	const uint32_t	alpha = color.a;
	const uint32_t	red = color.r;
	const uint32_t	green = color.g;
	const uint32_t	blue = color.b;

	return (alpha << 24 | red << 16 | green << 8 | blue);
}
