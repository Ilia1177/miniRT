#include <miniRT_bonus.h>

int	ambient_exist(t_data *scene)
{
	t_light	*light;

	light = scene->lights;
	while (light)
	{
		if (light->type == AMBIENT)
			return (1);
		light = light->next;
	}
	return (0);
}

int	go_to_endl(char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\n' && str[c])
		c++;
	return (c);
}

void	print_all(t_data *scene)
{
	t_object	*obj;
	t_light		*light;

	printf("**************************linked list OBJECT**************\n");
	obj = scene->objects;
	while (obj)
	{
		print_obj(*obj);
		obj = obj->next;
	}
	printf("**************************linked list LIGHT**************\n");
	light = scene->lights;
	while (light)
	{
		print_light(*light);
		light = light->next;
	}
	printf("****************************CAMERA **********************\n");
	print_cam(scene->cam);
}
