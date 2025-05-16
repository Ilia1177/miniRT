/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:24 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:14:25 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

t_argb	argb_mult(t_argb color, t_argb factor)
{
	t_argb	result;

	result.a = color.a * (factor.a / 255.0);
	result.r = color.r * (factor.r / 255.0);
	result.g = color.g * (factor.g / 255.0);
	result.b = color.b * (factor.b / 255.0);
	argb_clamp(&result);
	return (result);
}
