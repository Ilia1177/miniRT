/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_ease.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:57 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:59 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

t_argb	argb_ease(t_argb color, uint8_t ease)
{
	t_argb	result;

	result.a = ease - color.a;
	result.r = ease - color.r;
	result.g = ease - color.g;
	result.b = ease - color.b;
	argb_clamp(&result);
	return (color);
}
