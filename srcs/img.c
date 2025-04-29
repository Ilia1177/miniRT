/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:59:33 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/29 18:25:02 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	rt_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

//	not in usage for now
unsigned int	rt_get_pixel(t_img img, int x, int y)
{
	unsigned int	p;

	p = *(unsigned int *)((img.addr + (y * img.llen) + (x * img.bpp / 8)));
	return (p);
}
