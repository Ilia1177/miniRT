/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argb.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:14:58 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:15:22 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARGB_H
# define FT_ARGB_H
# include <stdint.h>

typedef struct s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
}	t_argb;

uint32_t	argb_toint(t_argb color);
t_argb		argb_ease(t_argb color, uint8_t ease);
void		argb_clamp(t_argb *color);
t_argb		argb_mult(t_argb color, t_argb factor);
t_argb		argb_add(t_argb color1, t_argb color2);
t_argb		argb_inverse(t_argb color);
t_argb		argb_fromint(int color);
t_argb		argb_applyalpha(t_argb color);

#endif
