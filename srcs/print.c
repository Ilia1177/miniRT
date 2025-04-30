/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:53:22 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/15 11:54:13 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*****************************************************************************
* Print message when an error is catched
* 109 is ascii code of m firt letter of malloc
******************************************************************************/
void	print_error_msg(int status, t_data *scene)
{
	if (status == -1)
		printf(MSG_BAD_POS);
	if (status == -2)
		printf(MSG_BAD_RGB);
	if (status == -3)
		printf(MSG_BAD_FLT);
	if (status == -4)
		printf(MSG_BAD_TYPE);
	if (status == -5)
		printf(MSG_BAD_LGHT);
	if (status == -6)
		printf(MSG_BAD_ELEM);
	if (status == -7)
		printf(MSG_BAD_LGHT);
	if (status == -8)
		printf(MSG_BAD_OPT);
	if (status == -109)
		printf(MSG_BAD_MALL);
	if (status == -9)
		printf(MSG_BAD_FILE);
	if (status == -10)
		printf(MSG_BAD_CAM);
	rt_shut_down(scene);
	exit (EXIT_FAILURE);
}

void	print_vec4(t_vec4 v, char *msg)
{
	printf("%s{x: %.1f, y: %.1f, z:%.1f}", msg, v.x, v.y, v.z);
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d", msg,
		color.a, color.r, color.g, color.b);
}

void	print_input(void)
{
	printf("+=============+\n\
|     MENU    |\n\
+=============+=============+=============+=============+\n\
|    CAM      |   OBJECT    |   OBJECT    |   OBJECT    |\n\
|-------------|-------------|-------------|-------------|\n\
|w : forward  |i : forward  |u : up       |c : rot.on z |\n\
|a : left     |j : left     |o : down     |v : bigger   |\n\
|d : right    |l : right    |z : rot.on x |b : smaller  |\n\
|s : backward |k : backward |x : rot.on y |n&m : cyl.   |\n\
+=============+=============+=============+=============+\n");
}
