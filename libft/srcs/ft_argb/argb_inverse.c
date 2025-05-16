/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb_inverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:16 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:14:19 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_argb.h"

t_argb	argb_inverse(t_argb color)
{
	t_argb	new_color;

	new_color.a = 255 - color.a;
	new_color.r = 255 - color.r;
	new_color.g = 255 - color.g;
	new_color.b = 255 - color.b;
	return (new_color);
}
