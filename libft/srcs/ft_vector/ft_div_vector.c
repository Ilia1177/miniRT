/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:40:35 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 17:42:38 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

t_vec4	div_vec4(t_vec4 vec, float d)
{
	t_vec4	result;

	result = (t_vec4){0, 0, 0, 0};
	if (d == 0.0f)
		return (result);
	result.x = vec.x / d;
	result.y = vec.y / d;
	result.z = vec.z / d;
	result.w = vec.w;
	return (result);
}

t_vec3	div_vec3(t_vec3 vec, float d)
{
	t_vec3	result;

	result = (t_vec3){0, 0, 0};
	if (d == 0.0f)
		return (result);
	result.x = vec.x / d;
	result.y = vec.y / d;
	result.z = vec.z / d;
	return (result);
}
