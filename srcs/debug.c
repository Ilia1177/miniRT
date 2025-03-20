#include <miniRT.h>

void	print_vec3(t_vec3 v, char *msg)
{
	printf("%s{x: %.1f, y: %.1f, z:%.1f}", msg, v.x, v.y, v.z);
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
	print_vec3(light.pos, "\tpos");
	print_vec3(light.dir, "\tdir");
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
	print_vec3(obj.pos, "\tpos");
	print_vec3(obj.orientation, "\tdir");
	//printf("\tpos : %.1f, %.1f, %.1f", obj.pos.x, obj.pos.y, obj.pos.z);
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
	print_vec3(camera.pos, "\tpos");
	print_vec3(camera.dir, "\tdir");
	print_vec3(camera.right, "\tright");
	print_vec3(camera.up, "\tup");
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
	if (status == -109)
		printf("Malloc error\n");
}
