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

void	rt_rect(const t_img *img, t_vec2 pos, t_vec2 size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size.x)
	{
		j = -1;
		while (++j < size.y)
			rt_put_pixel(img, pos.x + i, pos.y + j, color);
	}
}

t_img	*new_img(t_data *scene, char *path)
{
	t_img		*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->ptr = mlx_xpm_file_to_image(scene->mlx, path, &img->w, &img->h);
	if (!img->ptr)
		return (NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->llen, &img->endian);
	if (!img->addr)
		return (NULL);
	return (img);
}

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
