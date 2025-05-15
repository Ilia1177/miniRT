/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:03:44 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/12 15:00:36 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec4	add_vec4(t_vec4 a, t_vec4 b)
{
	t_vec4	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}
