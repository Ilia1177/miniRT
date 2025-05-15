/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:54:59 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/12 14:57:16 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

t_vec3	normalize_vec3(t_vec3 vec)
{
	t_vec3	result;
	float	lenght;

	lenght = mag_vec3(vec);
	result = div_vec3(vec, lenght);
	return (result);
}

t_vec4	normalize_vec4(t_vec4 vec)
{
	t_vec4	result;
	float	lenght;

	lenght = mag_vec4(vec);
	result = div_vec4(vec, lenght);
	result.w = vec.w;
	return (result);
}
