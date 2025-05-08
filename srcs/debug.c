/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:45:32 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/15 11:57:38 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_light(t_light light)
{
	if (light.type == POINT)
		printf("type : %s", "point");
	if (light.type == AMBIENT)
		printf("type : %s", "ambient");
	if (light.type == DIRECTIONAL)
		printf("type : %s", "directionnal");
	print_argb(light.intensity, "\tintensity");
	print_vec4(light.pos, "\tpos");
	print_vec4(light.dir, "\tdir");
	printf("\n");
}

void	print_obj(t_object obj)
{
	if (obj.type == SPHERE)
		printf("type : %s", "sphere");
	if (obj.type == PLANE)
		printf("type : %s", "plan");
	if (obj.type == CYLINDER)
		printf("type : %s", "cylinder");
	print_vec4(obj.pos, "\tpos");
	print_vec4(obj.axis, "\tdir");
	printf("\tpattern : %d", obj.pattern);
	printf("\tspecu : %d", obj.spec);
	printf("\tradius : %.1f", obj.radius);
	printf("\thight : %.1f", obj.height);
	print_argb(obj.reflect, "\treflective");
	print_argb(obj.color, "\tcolor");
	printf("\n");
}

void	print_cam(t_camera camera)
{
	printf("[-----------PRINT CAM-------------]\n");
	print_vec4(camera.pos, "pos");
	print_vec4(camera.dir, "\tdir");
	print_vec4(camera.right, "\tright");
	print_vec4(camera.up, "\tup");
	printf("\tfov : %d", camera.fov);
	printf("\tyaw : %.1f", camera.yaw);
	printf("\tpitch : %.1f\n", camera.pitch);
}

void	print_mat4(t_mat4 matrix)
{
	print_vec4(matrix.i, "i:");
	printf("\n");
	print_vec4(matrix.j, "j:");
	printf("\n");
	print_vec4(matrix.k, "k:");
	printf("\n");
	print_vec4(matrix.p, "p:");
	printf("\n");
}
