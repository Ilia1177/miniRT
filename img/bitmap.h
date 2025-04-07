/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:43:31 by tjouvenc          #+#    #+#             */
/*   Updated: 2025/03/08 14:13:34 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

-- a remplacer    # include "img.h"
# include <stdint.h>

# define BMP_MAGIC		0x4D42
# define HEADER_SIZE	26
//# define MAX_SIZE		0x10000C	// HEADER_SIZE + (1024 * 1024)
# define MAX_SIZE		0xFFFFFFFF // test

typedef struct s_bmp_header
{
	uint16_t	magic;
	uint32_t	size;
	uint32_t	reserved;
	uint32_t	data_offset;
	uint32_t	dib_size;
	uint16_t	dib_width;
	uint16_t	dib_height;
	uint16_t	dib_cp;
	uint16_t	dib_bpp;

	uint32_t	data_size; // Not actually part of the header
} __attribute__((packed))	t_bmp_header;

typedef struct s_24_c
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
} __attribute__((packed))	t_24_c;

char	*bitmap_load(t_data *scene, t_img *out, char *filename);

#endif
