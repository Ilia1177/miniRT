/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:55:05 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 13:59:31 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

float	dist_vec4(t_vec4 p1, t_vec4 p2)
{
	return (sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y)
			* (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z)));
}

t_vec4	cross_vec3(t_vec4 a, t_vec4 b)
{
	t_vec4	product;

	product.x = a.y * b.z - a.z * b.y;
	product.y = a.z * b.x - a.x * b.z;
	product.z = a.x * b.y - a.y * b.x;
	product.w = 0;
	return (product);
}

t_vec4	normalize_vec3(t_vec4 vec)
{
	t_vec4	result;
	float	lenght;

	lenght = mag_vec3(vec);
	result = div_vec3(vec, lenght);
	result.w = vec.w;
	return (result);
}

t_vec4	div_vec3(t_vec4 vec, float d)
{
	t_vec4	result;

	result = (t_vec4){0, 0, 0, 0};
	if (d == 0.0f)
		return (result);
	result.x = vec.x / d;
	result.y = vec.y / d;
	result.z = vec.z / d;
	result.w = 0;
	return (result);
}

t_vec4	mult_vec4(t_vec4 vec, float a)
{
	t_vec4	result;

	result.x = vec.x * a;
	result.y = vec.y * a;
	result.z = vec.z * a;
	result.w = 0;
	return (result);
}

float	dot_vec4(t_vec4 a, t_vec4 b)
{
	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

float	mag_vec3(t_vec4 a)
{
	float	result;

	result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (result);
}

t_vec4	sub_vec3(t_vec4 a, t_vec4 b)
{
	t_vec4	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}

t_vec4	add_vec3(t_vec4 a, t_vec4 b)
{
	t_vec4	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}
