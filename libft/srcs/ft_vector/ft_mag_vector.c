/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mag_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:55 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 17:49:29 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"
#include "../../include/libft.h"

float	mag_vec4(t_vec4 a)
{
	float	result;

	result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (result);
}

float	mag_vec3(t_vec3 a)
{
	float	result;

	result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	return (result);
}
