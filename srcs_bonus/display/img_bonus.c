/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:50:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 14:50:32 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rt_put_pixel(const t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

uint32_t	rt_get_pixel(t_img img, int x, int y)
{
	uint32_t	p;

	p = *(uint32_t *)((img.addr + (y * img.llen) + (x * img.bpp / 8)));
	return (p);
}
