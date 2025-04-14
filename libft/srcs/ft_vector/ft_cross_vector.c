/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cross_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:40:19 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 17:33:55 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

t_vec3	cross_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	product;

	product.x = a.y * b.z - a.z * b.y;
	product.y = a.z * b.x - a.x * b.z;
	product.z = a.x * b.y - a.y * b.x;
	return (product);
}

t_vec4	cross_vec4(t_vec4 a, t_vec4 b)
{
	t_vec4	product;

	product.x = a.y * b.z - a.z * b.y;
	product.y = a.z * b.x - a.x * b.z;
	product.z = a.x * b.y - a.y * b.x;
	product.w = a.w * b.w - a.w * b.w;
	return (product);
}
