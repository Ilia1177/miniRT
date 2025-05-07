/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_option_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:59:23 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 13:00:04 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

int	get_int_opt(char **line, int *num, int nb_char)
{
	char	*str;
	char	*end;
	int		status;

	status = 0;
	str = *line + nb_char;
	end = str;
	*num = (int)ft_strtof(str, &end);
	if (!(str != end && ft_isspace(*end)))
		status = -8;
	*line = end;
	return (status);
}

int	assign_opt(char **line, int *opt, int nb_char)
{
	*opt = 1;
	*line = *line + nb_char;
	return (0);
}

int	get_str_opt(char **line, char **opt, int nb_char)
{
	char	*str;
	int		len;
	char	*new_str;

	str = *line + nb_char + 1;
	len = 0;
	while (str[len] && ft_strcmp("\n", &str[len]) && !ft_isspace(str[len]))
		len++;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (-109);
	ft_strlcpy(new_str, str, len + 1);
	*opt = new_str;
	*line = str + len;
	return (0);
}

int	get_reflective(char **line, t_argb *c, int nb_char)
{
	char	*str;
	int		status;

	status = 0;
	str = *line + nb_char;
	status = str_to_argb(&str, c, 1);
	*line = str;
	return (status);
}

/*****************************************************************************
 	* Get (int)pattern (int)spec (t_argb)reflect of an object for bonus part
*****************************************************************************/
int	get_options(char **line, t_object *obj)
{
	char	*str;
	int		status;

	str = *line;
	str += skip_space(str);
	status = 0;
	while (str && *str && !status && ft_strcmp(str, "\n"))
	{
		if (!ft_strncmp("-p", str, 2))
			status = assign_opt(&str, &obj->pattern, 2);
		else if (!ft_strncmp("-spc", str, 4))
			status = get_int_opt(&str, &obj->spec, 4);
		else if (!ft_strncmp("-opt", str, 2))
			status = assign_opt(&str, &obj->opt, 4);
		else if (!ft_strncmp("-img", str, 4))
			status = get_str_opt(&str, &obj->path, 4);
		else if (!ft_strncmp("-ref", str, 4))
			status = get_reflective(&str, &obj->reflect, 4);
		else if (ft_strcmp("\n", str))
			status = -8;
		str += skip_space(str);
	}
	*line = str;
	return (status);
}
