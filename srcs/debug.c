#include <miniRT.h>

void	print_obj(t_object obj)
{
	printf("-----------PRINT OBJ-------------\n");
	printf("type : %d", obj.type);
	printf("\tpos : %.1f, %.1f, %.1f", obj.pos.x, obj.pos.y, obj.pos.z);
	printf(" specu : %d", obj.specular);
	printf(" radius : %.1f", obj.radius);
	printf(" height : %.1f", obj.height);
	printf(" reflective : %.1f", obj.reflective);
	printf(" color : %X\n", obj.color);
}
