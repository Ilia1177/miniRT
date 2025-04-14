/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:51:25 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 17:53:18 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"

t_vec4	mult_vec4(t_vec4 vec, float a)
{
	t_vec4	result;

	result.x = vec.x * a;
	result.y = vec.y * a;
	result.z = vec.z * a;
	result.w = vec.w;
	return (result);
}

t_vec3	mult_vec3(t_vec3 vec, float a)
{
	t_vec3	result;

	result.x = vec.x * a;
	result.y = vec.y * a;
	result.z = vec.z * a;
	return (result);
}
