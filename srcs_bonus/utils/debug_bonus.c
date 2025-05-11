/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:46:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/09 12:03:39 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	print_light(t_light light)
{
	if (light.type == POINT)
		printf("type : %s\n", "point");
	if (light.type == AMBIENT)
		printf("type : %s\n", "ambient");
	if (light.type == DIRECTIONAL)
		printf("type : %s\n", "directionnal\n");
	print_argb(light.intensity, "intensity");
	print_vec4(light.pos, "pos");
	print_vec4(light.dir, "dir");
	printf("\n");
}

void	print_obj(t_object obj)
{
	if (obj.type == SPHERE)
		printf("type : sphere\n");
	if (obj.type == PLANE)
		printf("type : plan\n");
	if (obj.type == CYLINDER)
		printf("type : cylinder\n");
	if (obj.type == HYPERBOL)
		printf("type : hyperboloid\n");
	print_mat4(obj.t_m);
	printf("pattern : %d\n", obj.pattern);
	printf("specu   : %d\n", obj.spec);
	printf("radius  : %.1f\n", obj.radius);
	printf("height  : %.1f\n", obj.height);
	printf("img     : %s\n", obj.path);
	printf("option  : %d\n", obj.opt);
	print_argb(obj.reflect, "reflective");
	print_argb(obj.color, "color");
	print_vec4(obj.scale, "scale:");
	printf("\n");
}

void	print_cam(t_camera camera)
{
	printf("camera :\n");
	print_mat4(camera.t_m);
	printf("yaw : %.1f, ", camera.yaw);
	printf("pitch : %.1f\n", camera.pitch);
}

void	print_mat4(t_mat4 matrix)
{
	print_vec4(matrix.i, "i:");
	print_vec4(matrix.j, "j:");
	print_vec4(matrix.k, "k:");
	print_vec4(matrix.p, "p:");
}
