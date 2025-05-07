/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:44:41 by npolack           #+#    #+#             */
/*   Updated: 2025/04/10 12:10:26 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

//	float dist_vec3(t_vec4 p1, t_vec4 p2)
//	{
//		float	dist;
//
//		dist = (p2.x - p1.x) * (p2.x - p1.x) +
//			(p2.y - p1.y) * (p2.y - p1.y) +
//			(p2.z - p1.z) * (p2.z - p1.z);
//		dist = ft_sqrtf(dist);
//		return (dist);
//	}
//
//	t_vec4 cross_vec4(t_vec4 a, t_vec4 b)
//	{
//		t_vec4 product;
//
//		product.x = a.y * b.z - a.z * b.y;
//		product.y = a.z * b.x - a.x * b.z;
//		product.z = a.x * b.y - a.y * b.x;
//		product.w = 0;
//		return (product);
//	}
//
//	t_vec4	normalize_vec4(t_vec4 vec)
//	{
//		t_vec4	result;
//		float	lenght;
//
//		lenght = mag_vec3(vec);
//		if (lenght < 0.001f)
//			lenght = 1.0f;
//		result = div_vec4(vec, lenght);
//		result.w = 0;
//		return (result);
//	}
//
//	t_vec4	div_vec4(t_vec4 vec, float d)
//	{
//		t_vec4	result;
//
//		result = (t_vec4) {0, 0, 0, 0};
//		if (d == 0.0f)
//			return (result);
//		result.x = vec.x / d;
//		result.y = vec.y / d;
//		result.z = vec.z / d;
//		result.w = vec.w;
//		return (result);
//	}
//
//	t_vec4	mult_vec4(t_vec4 vec, float a)
//	{
//		t_vec4	result;
//
//		result.x = vec.x * a;
//		result.y = vec.y * a;
//		result.z = vec.z * a;
//		result.w = vec.w;
//		return (result);
//	}
//
//	float dot_vec3(t_vec4 a, t_vec4 b)
//	{
//
//		float	result;
//
//		result = a.x * b.x + a.y * b.y + a.z * b.z;
//		return (result);
//	}
//
//	float dot_vec4(t_vec4 a, t_vec4 b)
//	{
//
//		float	result;
//
//		result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
//		return (result);
//	}
//
//	float	mag_vec4(t_vec4 a)
//	{
//		float	result;
//
//		result = ft_sqrtf(ft_powf(a.x, 2) + ft_powf(a.y, 2) + ft_powf(a.z, 2));
//		return (result);
//	}
//
//	t_vec4	sub_vec4(t_vec4 a, t_vec4 b)
//	{
//		t_vec4 result;
//
//		result.x = a.x - b.x;
//		result.y = a.y - b.y;
//		result.z = a.z - b.z;
//		result.w = a.w - b.w;
//		return (result);
//	}
//
//	t_vec4	add_vec4(t_vec4 a, t_vec4 b)
//	{
//		t_vec4 result;
//
//		result.x = a.x + b.x;
//		result.y = a.y + b.y;
//		result.z = a.z + b.z;
//		result.w = a.w + b.w;
//		return (result);
//	}
