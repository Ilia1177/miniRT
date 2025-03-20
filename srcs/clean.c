#include <miniRT.h>

void	free_light(t_light *light)
{
	t_light	*old_light;

	while (light)
	{
		old_light = light;
		light = light->next;
		free(old_light);
	}
}

void	free_objects(t_object **obj)
{
	t_object	*temp_obj;

	if (!obj)
		return ;
	while (*obj)
	{
		temp_obj = (*obj)->next;
		free(*obj);
		*obj = temp_obj;
	}
}

void	free_data(t_data *scene)
{
	free_light(scene->lights);
	free_objects(&scene->objects);
}
