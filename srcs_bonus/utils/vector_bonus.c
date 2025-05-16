/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:09:41 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/16 15:12:23 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// Generate two random numbers in [0, 1)
// Convert to spherical coordinates
// Compute Cartesian coordinates on the unit sphere
// Scale to the desired magnitude
t_vec4	random_vec4(float magnitude)
{
	t_vec4	vec;
	t_uv	uv;
	double	theta;
	double	phi;
	double	sin_phi;

	uv.u = (double)rand() / RAND_MAX;
	uv.v = (double)rand() / RAND_MAX;
	theta = 2.0f * M_PI * uv.u;
	phi = acos(2.0f * uv.v - 1.0);
	sin_phi = sin(phi);
	vec.x = sin_phi * cos(theta);
	vec.y = sin_phi * sin(theta);
	vec.z = cos(phi);
	vec.x = vec.x * magnitude;
	vec.y = vec.y * magnitude;
	vec.z = vec.z * magnitude;
	return (vec);
}
