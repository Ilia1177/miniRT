/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:53:22 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 13:00:15 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

void	print_error_arg(int status)
{
	if (status == 11)
		printf("not enought args. Usage: ..."); // describe usage
	if (status == 12)
		printf("map name not conform.");
	if (status == 13)
		printf("map in \".rt\" format needed.");
	if (status == 14)
		printf("???"); // to be explicit
}

void	print_error_mlx(int status)
{
	if (status == 21)
		printf(MSG_BAD_MLX);
	if (status == 22)
		printf(MSG_BAD_WIN);
	if (status == 23)
		printf(MSG_BAD_IMG);
	if (status == 24)
		printf(MSG_BAD_ADD);
}

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
	print_error_mlx(status);
	print_error_arg(status);
	rt_shut_down(scene);
	exit (EXIT_FAILURE);
}

void	print_vec4(t_vec4 v, char *msg)
{
	printf("%s{x: %.3f, y: %.3f, z:%.3f, w:%.3f}\n", msg, v.x, v.y, v.z, v.w);
}

void	print_argb(t_argb color, char *msg)
{
	printf("%s: a: %d, r: %d, g: %d, b %d\n", msg,
		color.a, color.r, color.g, color.b);
}

void	print_input(void)
{
	printf("+=============+\n\
	|     MENU    |\n\
	+=============+=============+=============+=============+\n\
	|    CAM      | translation |  rotation   | scale (obj) |\n\
	|-------------|-------------|-------------|-------------|\n\
	|w: forward   |u/o: +/- (y) |z: + on x    |r/f: +/- (x) |\n\
	|a: left      |i/k: +/- (z) |x: + on y    |t/g: +/- (y) |\n\
	|d: right     |h/k: +/- (x) |c: + on z    |y/h: +/- (z) |\n\
	|s: backward  |             |             | 			|\n\
	|q: up	      |             |             | 			|\n\
	|e: down	  |             |             | 			|\n\
	+=============+=============+=============+=============+\n");
}
