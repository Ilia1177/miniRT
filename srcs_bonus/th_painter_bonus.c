/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_painter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:35:36 by jhervoch          #+#    #+#             */
/*   Updated: 2025/05/07 13:37:07 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_bonus.h>

void	th_annouce(char *msg, t_painter *painter)
{
	t_data			*scene;

	scene = (t_data *)painter->sceneref;
	pthread_mutex_lock(&scene->announce);
	printf("%lld painter %d: %s",
		time_from(&scene->start) / 1000, painter->id, msg);
	pthread_mutex_unlock(&scene->announce);
}

void	*th_mastering(void *sceneref)
{
	t_data	*scene;

	scene = (t_data *)sceneref;
	mlx_loop(scene->mlx);
	return (NULL);
}

int	th_master_start(t_data *scene)
{
	pthread_t	master;

	if (pthread_create(&master, NULL, &th_mastering, scene))
	{
		perror("master start:");
		return (1);
	}
	pthread_join(master, NULL);
	return (0);
}

void	*th_painter_draw(void *worker)
{
	t_painter	*painter;
	t_data		*scene;

	painter = (t_painter *)worker;
	scene = painter->sceneref;
	while (1)
	{
		th_annouce("start\n", painter);
		pthread_mutex_lock(&scene->print);			// protection for scene->processing
		if (!scene->processing)						// if the simulation is not running, then quit.
		{
			th_annouce("exit\n", painter);
			pthread_mutex_unlock(&scene->print);
			break ;
		}
		pthread_mutex_unlock(&scene->print);
		display_color(painter);						// throw_ray & write colors to scene->img
        pthread_mutex_lock(&scene->print); 			// lock
		scene->at_rest++; 							// painter is done writing colors
		th_annouce("done\n", painter);													// 
		if (scene->at_rest == THREAD_NB)			// last thread send signal to unlock master
			pthread_cond_signal(&scene->master_rest);
		th_annouce("wait\n", painter);
		while (scene->processing && scene->at_rest)	// threads wait until master unlock them (if scene->at_rest == 0)
			pthread_cond_wait(&scene->painter_rest, &scene->print);
		pthread_mutex_unlock(&scene->print);
	}
	return NULL;
}

void	th_painer_quit(t_data *scene)
{
	(void)scene;
	return ;
}



void	th_painter_kill(t_data *scene)
{
	int i;

	printf("Revoke painter...\n");
	i = 0;
	while (i < THREAD_NB)
	{
		printf("killing painter %d.\n", scene->painter[i].id);
		scene->painter[i].done = 1;
		i++;
	}
	printf("All painter are done!\n");
}

int th_painter_wait(t_data *scene)
{
	int	i;

	printf("Wait for painters to finish...\n");
	i = -1;
	while (++i < THREAD_NB)
	{
		pthread_join(scene->painter[i].itself, NULL);
		printf("Painter %d/%d gone !", scene->painter[i].id, THREAD_NB);
	}
	printf("All painters are gone. (bye bye)\n");
	return (0);
}
int	th_painter_start(t_data *scene)
{
	int	i;

	i = 0;
	while (i < THREAD_NB)
	{
		scene->painter[i] = th_painter_init(scene, i);
		if (pthread_create(&scene->painter[i].itself, NULL, &th_painter_draw, &scene->painter[i]))
		{
			perror("thread start:");
			//rt_shut_down(scene);
			return (1);
		}
		i++;
	}
	return (0);
}
