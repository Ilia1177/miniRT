#include <miniRT.h>

void	free_sphere(t_sphere *sphere)
{
	t_sphere	*old_sphere;

	while (sphere)
	{
		old_sphere = sphere;
		sphere = sphere->next;
		free(old_sphere);
	}
}

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
		
