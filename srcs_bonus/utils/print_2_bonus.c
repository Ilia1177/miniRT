/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:10:26 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 15:10:50 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	print_vec4(t_vec4 v, char *msg)
{
	printf("%s{x: %.3f, y: %.3f, z:%.3f, w:%.3f}\n", msg, v.x, v.y, v.z, v.w);
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d\n", msg,
		color.a, color.r, color.g, color.b);
}
