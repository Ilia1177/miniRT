/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:37:03 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/03 19:37:26 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	init_obj(t_object *obj, t_type type)
{
	ft_bzero(obj, sizeof(t_object));
	obj->type = type;
	obj->t = T_MAX;
	obj->pos = (t_vec4){0, 0, 0, 1};
	obj->axis = (t_vec4){0, 0, 0, 0};
	obj->dir = (t_vec4){0, 0, 1, 0};
	obj->up = (t_vec4){0, 1, 0, 0};
	obj->right = (t_vec4){1, 0, 0, 0};
	obj->spec = SPECULAR;
	obj->next = NULL;
}
