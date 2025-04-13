#include <miniRT_bonus.h>

void	*th_mastering(void *sceneref)
{
	t_data *scene;

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
	t_painter *painter;
	t_data	*scene;

	painter = (t_painter *)worker;
	scene = painter->sceneref;
	while (1)
	{
		pthread_mutex_lock(&scene->print);
		if (!scene->processing)
		{
			pthread_mutex_unlock(&scene->print);
			break ;
		}
		pthread_mutex_unlock(&scene->print);

		//printf("is painting\n");
		display_color(scene, painter);


        pthread_mutex_lock(&scene->print); // lock
		scene->at_rest++;
		//printf("at rest: %d\n", scene->at_rest);
		if (scene->at_rest == THREAD_NB)
			pthread_cond_signal(&scene->master_rest);

		//printf("is done: %d\n", painter->done);
		while (scene->processing && scene->at_rest)
			pthread_cond_wait(&scene->painter_rest, &scene->print); // wait
		pthread_mutex_unlock(&scene->print);
	}

	return NULL;
}

void	th_painer_quit(t_data *scene)
{
	(void)scene;
	return ;
}


t_painter	th_painter_init(t_data *scene, int i)
{
	t_painter new;

	ft_bzero(&new, sizeof(new));
	new.brush = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	new.cnv = scene->cnv;
	new.vp = scene->viewport;
	new.sceneref = (t_data *)scene;
	new.id = i + 1;
	return (new);
}

void	th_painter_kill(t_data *scene)
{
	int i;

	printf("Revoke painter!\n");
	i = 0;
	while (i < THREAD_NB)
	{
		printf("killing painter %d\n", scene->painter[i].id);
		scene->painter[i].done = 1;
		i++;
	}
	printf("all painter are done!\n");
}

int th_painter_wait(t_data *scene)
{
	int	i;

	printf("wait for thread to finish\n");
	i = -1;
	while (++i < THREAD_NB)
	{
		pthread_join(scene->painter[i].itself, NULL);
		printf("Painter %d gone", scene->painter[i].id);
	}
	printf("All painters are gone (bye bye)\n");
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
			rt_shut_down(scene);
			return (1);
		}
		i++;
	}
	return (0);
}
