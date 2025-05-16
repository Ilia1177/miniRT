/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:21 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:29 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

t_argb	argb_add(t_argb color1, t_argb color2)
{
	t_argb			result;

	result.a = color1.a + color2.a;
	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	argb_clamp(&result);
	return (result);
}
