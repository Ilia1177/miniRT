/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:04:36 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 17:39:30 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vector.h"
#include <math.h>

float	dist_vec3(t_vec3 p1, t_vec3 p2)
{
	return (sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y)
			* (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z)));
}

float	dist_vec4(t_vec4 p1, t_vec4 p2)
{
	float	dist;

	dist = (p2.x - p1.x) * (p2.x - p1.x)
		+ (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z);
	return (sqrtf(dist));
}
