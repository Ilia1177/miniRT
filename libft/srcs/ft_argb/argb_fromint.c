/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_fromint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:09 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:14:11 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

t_argb	argb_fromint(int color)
{
	t_argb	argb_color;

	argb_color.a = (color >> 24) & 0xFF;
	argb_color.r = (color >> 16) & 0xFF;
	argb_color.g = (color >> 8) & 0xFF;
	argb_color.b = color & 0xFF;
	return (argb_color);
}
