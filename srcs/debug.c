#include <miniRT.h>

void	print_vec3(t_vec3 v, char *msg)
{
	printf("%s{x: %.1f, y: %.1f, z:%.1f}", msg, v.x, v.y, v.z );
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d",msg, color.a, color.r, color.g, color.b);
}
void	print_obj(t_object obj)
{
	printf("-----------PRINT OBJ-------------\n");
	printf("type : %d", obj.type);
	print_vec3(obj.pos, "\tpos");
	//printf("\tpos : %.1f, %.1f, %.1f", obj.pos.x, obj.pos.y, obj.pos.z);
	printf(" specu : %d", obj.specular);
	printf(" radius : %.1f", obj.radius);
	printf(" height : %.1f", obj.height);
	print_argb(obj.reflective, "reflective");
	print_argb(obj.color, "color");
	printf("\n");
}
