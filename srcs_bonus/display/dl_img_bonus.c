/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_img_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:46:47 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/08 15:21:49 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

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
