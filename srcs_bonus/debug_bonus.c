#include <miniRT_bonus.h>

void	print_vec4(t_vec4 v, char *msg)
{
	printf("%s{x: %.3f, y: %.3f, z:%.3f, w: %.3f}\n", msg, v.x, v.y, v.z, v.w);
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d",msg, color.a, color.r, color.g, color.b);
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

void print_cam(t_camera camera)
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
{ // for loop
	print_vec4(matrix.i, "i:");
	print_vec4(matrix.j, "j:");
	print_vec4(matrix.k, "k:");
	print_vec4(matrix.p, "p:");
}
