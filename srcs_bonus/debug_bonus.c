#include <miniRT_bonus.h>

void	print_vec4(t_vec4 v, char *msg)
{
	printf("%s{x: %.3f, y: %.3f, z:%.3f, w: %.3f}\n", msg, v.x, v.y, v.z, v.w);
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d\n",msg, color.a, color.r, color.g, color.b);
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
	if (obj.type == SPHERE)
		printf("type : sphere\n");
	if (obj.type == PLANE)
		printf("type : plan\n");
	if (obj.type == CYLINDER)
		printf("type : cylinder\n");
	if (obj.type == HYPERBOL)
		printf("type : hyperboloid\n");
	print_mat4(obj.t_m);
	printf("\tpattern : %d", obj.pattern);
	printf("\tspecu : %d", obj.spec);
	printf("\tradius : %.1f", obj.radius);
	printf("\thight : %.1f", obj.height);
	print_argb(obj.reflect, "\treflective");
	print_argb(obj.color, "\tcolor");
	print_vec4(obj.scale, "scale:");
	printf("\n");
}

void print_cam(t_camera camera)
{
	printf("camera :\n");
	print_mat4(camera.t_m);
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
		printf("Error\nBad position arguments\n");
	if (status == -2)
		printf("Error\nBad rgb arguments\n");
	if (status == -3)
		printf("Error\nBad float arguments\n");
	if (status == -4)
		printf("Error\nBad type arguments, only A,C,L,sp,pl,cy allowed\n");
	if (status == -5)
		printf("Error\nWrong number of light: only one ambient and one spot\n");
	if (status == -6)
		printf("Error\nWrong number of element: at least one sphere, one cylinder, one plane\n");
	if (status == -7)
		printf("Error\nWrong number of light: only one ambient, one point\n");
	if (status == -8)
		printf("Error\nWrong options arguments\n");
	if (status == -109)
		printf("Malloc error\n");
}

void print_mat4(t_mat4 matrix)
{ 
	print_vec4(matrix.i, "i:");
	print_vec4(matrix.j, "j:");
	print_vec4(matrix.k, "k:");
	print_vec4(matrix.p, "p:");
}
