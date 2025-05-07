/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:46:17 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 14:46:30 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

void	print_light(t_light light)
{
	if (light.type == POINT)
		printf("type : %s", "point");
	if (light.type == AMBIENT)
		printf("type : %s", "ambient");
	if (light.type == DIRECTIONAL)
		printf("type : %s", "directionnal\n");
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
	printf("specu : %d\n", obj.spec);
	printf("radius : %.1f\n", obj.radius);
	printf("hight : %.1f\n", obj.height);
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

void	print_painter(t_painter *painter)
{
	printf("PAINTER %d\n --> lim[0]: %f lim[1]: %f\n",
		painter->id, painter->lim[0], painter->lim[1]);
	print_vec4(painter->ray.o, "ray->o:");
	print_vec4(painter->ray.d, "ray->d:");
	print_vec4(painter->ray.v, "ray->v:");
	print_vec4(painter->ray.n, "ray->n:");
}
