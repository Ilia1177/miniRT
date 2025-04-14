/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dot_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:44:38 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 17:45:52 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

float	dot_vec3(t_vec4 a, t_vec4 b)
{
	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z;
	return (result);
}

float	dot_vec4(t_vec4 a, t_vec4 b)
{
	float	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (result);
}
