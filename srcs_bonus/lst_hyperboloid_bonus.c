#include <miniRT_bonus.h>

int	create_hyperboloid(char **line, t_data *scene)
{
	char		*str;
	t_object	hyperb;
	int			status;

	str = *line + 2 ;
	init_obj(&hyperb, HYPERBOL);
	status = str_to_vec4(&str, &hyperb.t_m.p, 1.0f);
	if (!status)
		status = str_to_vecdir(&str, &hyperb.t_m.k);
	if (!status)
		status = str_to_vec4(&str, &hyperb.scale, 2.0f);
	if (!status)
		status = str_to_float(&str, &hyperb.height);
	if (!status)
		status = str_to_argb(&str, &hyperb.color, 0);
	if (!status)
		status = get_options(&str, &hyperb);
	if (!status)
		status = make_object(hyperb, &scene->objects);
	*line = str + skip_space(str);
	return (status);
}
