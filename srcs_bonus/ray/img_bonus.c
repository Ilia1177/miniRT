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

void	save_pixel_data(t_img *img, int width, int height, int fd)
{
	t_vec2	pos;
	int		color;
	t_argb	argb;

	pos.y = 0;
	while (pos.y < height)
	{
		pos.x = 0;
		while (pos.x < width)
		{
			color = rt_get_pixel(*img, pos.x, pos.y);
			argb.r = (color >> 16) & 0xFF;
			argb.g = (color >> 8) & 0xFF;
			argb.b = (color) & 0xFF;
			write(fd, &argb.r, 1);
			write(fd, &argb.g, 1);
			write(fd, &argb.b, 1);
			pos.x++;
		}
		pos.y++;
	}
}

void	save_as_ppm(t_img *img, char *filename)
{
	const int	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if (fd < 0)
		return ;
	ft_dprintf(fd, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
	save_pixel_data(img, WIDTH, HEIGHT, fd);
	close(fd);
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
