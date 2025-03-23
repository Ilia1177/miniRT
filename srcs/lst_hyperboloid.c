#include <miniRT.h>


int	make_hyperboloid(t_object data, t_object **objects)
{
	t_object	*curr_cylinder;
	t_object	*new_cylinder;

	new_cylinder = malloc(sizeof(t_object));
	if (!new_cylinder)
		return (-109);
	ft_memcpy(new_cylinder, &data, sizeof(t_object));
	new_cylinder->next = NULL;
	curr_cylinder = NULL;
	if (*objects == NULL)
		*objects = new_cylinder;
	else
	{
		curr_cylinder = *objects;
		while (curr_cylinder->next)
			curr_cylinder = curr_cylinder->next;
		curr_cylinder->next = new_cylinder;
	}
	return (0);
}
