/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:39:43 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 10:40:27 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	move_camera_forward(t_camera *cam, float speed)
{
	cam->pos.x += cam->dir.x * speed;
	cam->pos.y += cam->dir.y * speed;
	cam->pos.z += cam->dir.z * speed;
}

void	move_camera_backward(t_camera *cam, float speed)
{
	cam->pos.x -= cam->dir.x * speed;
	cam->pos.y -= cam->dir.y * speed;
	cam->pos.z -= cam->dir.z * speed;
}

void	move_camera_right(t_camera *cam, float speed)
{
	cam->pos.x += cam->right.x * speed;
	cam->pos.y += cam->right.y * speed;
	cam->pos.z += cam->right.z * speed;
}

void	move_camera_left(t_camera *cam, float speed)
{
	cam->pos.x -= cam->right.x * speed;
	cam->pos.y -= cam->right.y * speed;
	cam->pos.z -= cam->right.z * speed;
}
