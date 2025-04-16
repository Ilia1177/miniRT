/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:45:32 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 10:56:54 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	print_vec4(t_vec4 v, char *msg)
{
	printf("%s{x: %.1f, y: %.1f, z:%.1f}", msg, v.x, v.y, v.z);
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d", msg,
		color.a, color.r, color.g, color.b);
}

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
	//printf("-----------PRINT OBJ-------------\n");
	if (obj.type == SPHERE)
		printf("type : %s", "sphere");
	if (obj.type == PLANE)
		printf("type : %s", "plan");
	if (obj.type == CYLINDER)
		printf("type : %s", "cylinder");
	print_vec4(obj.pos, "\tpos");
	print_vec4(obj.axis, "\tdir");
	//printf("\tpos : %.1f, %.1f, %.1f", obj.pos.x, obj.pos.y, obj.pos.z);
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
	printf("\tyaw : %.1f", camera.yaw);
	printf("\tpitch : %.1f\n", camera.pitch);
}

/*****************************************************************************
* Print message when an error is catched
* 109 is ascii code of m firt letter of malloc
******************************************************************************/
void	print_error_msg(int status)
{
	if (status == -1)
		printf(MSG_BAD_POS);
	if (status == -2)
		printf(MSG_BAD_RGB);
	if (status == -3)
		printf(MSG_BAD_FLT);
	if (status == -4)
		printf(MSG_BAD_TYPE);
	if (status == -5)
		printf(MSG_BAD_LGHT);
	if (status == -6)
		printf(MSG_BAD_ELEM);
	if (status == -7)
		printf(MSG_BAD_LGHT);
	if (status == -8)
		printf(MSG_BAD_OPT);
	if (status == -109)
		printf(MSG_BAD_MALL);
}

void	print_matrix(t_matrix matrix)
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
