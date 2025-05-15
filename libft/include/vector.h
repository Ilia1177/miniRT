/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:34:24 by npolack           #+#    #+#             */
/*   Updated: 2025/05/12 15:26:13 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

t_vec4	cross_vec4(t_vec4 a, t_vec4 b);
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);

float	dist_vec4(t_vec4 p1, t_vec4 p2);
float	dist_vec3(t_vec3 p1, t_vec3 p2);

t_vec4	div_vec4(t_vec4 vec, float d);
t_vec3	div_vec3(t_vec3 vec, float d);

float	dot_vec4(t_vec4 a, t_vec4 b);
float	dot_vec3(t_vec4 a, t_vec4 b);

float	mag_vec4(t_vec4 a);
float	mag_vec3(t_vec3 a);

t_vec4	mult_vec4(t_vec4 vec, float a);
t_vec3	mult_vec3(t_vec3 vec, float a);

t_vec4	normalize_vec4(t_vec4 vec);
t_vec3	normalize_vec3(t_vec3 vec);

t_vec4	sub_vec4(t_vec4 a, t_vec4 b);
t_vec3	sub_vec3(t_vec3 a, t_vec3 b);

t_vec4	add_vec4(t_vec4 a, t_vec4 b);
t_vec3	add_vec3(t_vec3 a, t_vec3 b);

#endif
