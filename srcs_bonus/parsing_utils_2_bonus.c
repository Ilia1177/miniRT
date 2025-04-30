#include <miniRT_bonus.h>

int	check_nb_obj(t_data *scene)
{
	int			nb_sphere;
	int			nb_plane;
	int			nb_cylinder;
	t_object	*curr_obj;

	nb_sphere = 0;
	nb_cylinder = 0;
	nb_plane = 0;
	curr_obj = scene->objects;
	while (curr_obj)
	{
		if (curr_obj->type == SPHERE)
			nb_sphere++;
		if (curr_obj->type == CYLINDER)
			nb_cylinder++;
		if (curr_obj->type == PLANE)
			nb_plane++;
		curr_obj = curr_obj->next;
	}
	if (!nb_sphere || !nb_cylinder || !nb_plane)
		return (-6);
	return (0);
}

int	check_nb_light(t_data *scene)
{
	int			nb_ambient;
	int			nb_point;
	t_light		*curr_light;

	nb_ambient = 0;
	nb_point = 0;
	curr_light = scene->lights;
	while (curr_light)
	{
		if (curr_light->type == AMBIENT)
			nb_ambient++;
		if (curr_light->type == POINT)
			nb_point++;
		curr_light = curr_light->next;
	}
	if (nb_point != 1 || nb_ambient != 1)
		return (-7);
	return (0);
}
