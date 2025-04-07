/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjouvenc <tjouvenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:09:32 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/04/07 11:35:02 by tjouvenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"

#include <unistd.h>
#include <fcntl.h>
#include "strings.h"
#include "libft.h"

static char	*raise_result(char *err, int fd, t_24_c *arr)
{
	if (fd >= 0)
		close(fd);
	if (arr)
		free(arr);
	return (err);
}

static char	*check_header(t_bmp_header *header, int fd)
{
	uint64_t	expected_size;

	if (header->magic != BMP_MAGIC)
		return (raise_result(ERR_INVALID_MAGIC, fd, NULL));
	if (header->size <= HEADER_SIZE || header->size > MAX_SIZE)
		return (raise_result(ERR_SIZE_OOB, fd, NULL));
	if (header->data_offset != HEADER_SIZE)
		return (raise_result(ERR_INVALID_OFFSET, fd, NULL));
	if (header->dib_size != 12)
		return (raise_result(ERR_INVALID_DIB, fd, NULL));
	header->data_size = header->size - HEADER_SIZE;
	expected_size = 3 * (header->dib_height
			* (header->dib_width + header->dib_width % 4));
	if (header->data_size != expected_size)
		return (raise_result(ERR_INVALID_RATIO, fd, NULL));
	if (header->dib_bpp != 24)
		return (raise_result(ERR_INVALID_BPP, fd, NULL));
	if (header->dib_cp != 1)
		return (raise_result(ERR_INVALID_CP, fd, NULL));
	return (NULL);
}

static void	fill_image(t_24_c *arr, t_bmp_header *header, t_img *img)
{
	t_24_c		col_in;
	t_color		col_out;
	t_point		pos;

	pos.y = header->dib_height - 1;
	while (pos.y >= 0)
	{
		pos.x = 0;
		while (pos.x < header->dib_width)
		{
			col_in = *arr++;
			col_out = col_in.r << 16 | col_in.g << 8 | col_in.b;
			*(img->data + (img->size.x * pos.y + pos.x)) = col_out;
			pos.x++;
		}
		arr = (t_24_c *)((char *)arr + header->dib_width % 4);
		pos.y--;
	}
}

char	*bitmap_load(t_gfx *gfx, t_img *out, char *filename)
{
	int				fd;
	t_bmp_header	header;
	t_24_c			*arr;
	char			*err;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (raise_result(ERR_OPEN_FAILED, -1, NULL));
	if (read(fd, &header, HEADER_SIZE) != HEADER_SIZE)
		return (raise_result(ERR_READ_FAILED, fd, NULL));
	err = check_header(&header, fd);
	if (err)
		return (raise_result(err, fd, NULL));
	arr = (t_24_c *)malloc(header.data_size);
	if (!arr)
		return (raise_result(ERR_MALLOC, fd, NULL));
	if (read(fd, arr, header.data_size) != header.data_size)
		return (raise_result(ERR_INVALID_SIZE, fd, arr));
	if (read(fd, arr, 1))
		return (raise_result(ERR_INVALID_SIZE, fd, arr));
	if (!img_init(gfx, out, point(header.dib_width, header.dib_height)))
		return (raise_result(ERR_MALLOC, fd, arr));
	fill_image(arr, &header, out);
	return (raise_result(NULL, fd, arr));
}
