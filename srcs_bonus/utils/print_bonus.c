/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:53:22 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/11 11:37:19 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	print_error_arg(int status)
{
	if (status == 11)
		printf("not enought args. Usage: *.rt files needed");
	if (status == 12)
		printf("map name not conform.");
	if (status == 13)
		printf("map in \"*.rt\" format needed.");
}

static void	print_error_mlx(int status)
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

static void	print_error_elem(int status)
{
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
	if (status == -109)
		printf(MSG_BAD_MALL);
	if (status == -9)
		printf(MSG_BAD_FILE);
	if (status == -10)
		printf(MSG_BAD_CAM);
	print_error_elem(status);
	print_error_mlx(status);
	print_error_arg(status);
	rt_shut_down(scene);
	exit (EXIT_FAILURE);
}

void	print_input(void)
{
	printf("+=============+\n\
|     MENU    |\n\
+=============+=============+=============+=============+==============+\n\
|    CAM      | translation |  rotation   | scale (obj) |    LIGHT     |\n\
|-------------|-------------|-------------|-------------|--------------|\n\
|w: forward   |u/o: +/- (y) |z: + on x    |r/f: +/- (x) |1 : backward  |\n\
|a: left      |i/k: +/- (z) |x: + on y    |t/g: +/- (y) |3 : forward   |\n\
|d: right     |h/k: +/- (x) |c: + on z    |y/h: +/- (z) |4-6 : lt.rgt. |\n\
|s: backward  |             |             |             |2-8 : up-down |\n\
|q: up        |             |             |             |F5 : next lt  |\n\
|e: down      |             |             |             |              |\n\
+=============+=============+=============+=============+==============+\n");
}
