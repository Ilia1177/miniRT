/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:01:42 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:01 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_board	checkerboard(t_argb color1, t_argb color2)
{
	t_board	tab;
	int		i;
	int		j;

	j = 0;
	while (j < CBOARD_H)
	{
		i = 0;
		while (i < CBOARD_W)
		{
			if ((i + j) % 2 == 0)
				tab.color[j][i] = color1;
			else
				tab.color[j][i] = color2;
			i++;
		}
		j++;
	}
	return (tab);
}

t_argb	checkerboard_at(float u, float v, t_argb obj_color)
{
	t_argb			color;
	const t_board	tab = checkerboard(obj_color, argb_inverse(obj_color));
	int				u2;
	int				v2;

	v2 = fminf(floorf(v * CBOARD_H), CBOARD_H - 1);
	u2 = fminf(floorf(u * CBOARD_W), CBOARD_H - 1);
	color = tab.color[v2][u2];
	return (color);
}

t_argb	img_at(float u, float v, t_img *img)
{
	t_argb		color;
	t_uv		uv2;

	ft_bzero(&color, sizeof(color));
	if (!img || !img->addr)
		return (color);
	uv2.u = fminf(floor(u * img->w), img->w);
	uv2.v = fminf(floor(v * img->h), img->h);
	uv2.u = uv2.u + floor(img->w / 1.0f);
	color = argb_fromint(rt_get_pixel(*img, uv2.u, uv2.v));
	return (color);
}

/*****************************************************************************
 	* hp = hit point
******************************************************************************/
t_argb	mapping(t_ray *ray, t_object *obj)
{
	t_uv	uv;
	t_argb	color;
	t_vec4	hp;

	if (!(obj->pattern || (obj->path && !obj->normal_map)))
		return (obj->color);
	hp = mat_apply(mat_inverse(obj->t_m), ray->o);
	uv = get_uv(obj, hp);
	if (obj->pattern)
		color = checkerboard_at(uv.u, uv.v, obj->color);
	else
		color = img_at(uv.u, uv.v, obj->img);
	return (color);
}
