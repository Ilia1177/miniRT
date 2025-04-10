/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:34:24 by npolack           #+#    #+#             */
/*   Updated: 2025/04/10 11:43:19 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4

t_vec4	cross_vec4(t_vec4 a, t_vec4 b);
float	dot_vec4(t_vec4 a, t_vec4 b);
float	dot_vec3(t_vec4 a, t_vec4 b);
float	mag_vec4(t_vec4 a);
double	dist_vec4(t_vec4 a, t_vec4 b);
t_vec4	sub_vec4(t_vec4 a, t_vec4 b);
t_vec4	add_vec4(t_vec4 a, t_vec4 b);
t_vec4	normalize_vec4(t_vec4 vec);
t_vec4	div_vec4(t_vec4 vec, float d);
t_vec4	mult_vec4(t_vec4 vec, float a);
float	dist_vec4(t_vec4 a, t_vec4 b);
