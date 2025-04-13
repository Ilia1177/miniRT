#include <miniRT_bonus.h>

void	*th_listen(void *sceneref)
{
	t_data *scene;

	scene = (t_data *)sceneref;
	mlx_loop(scene->mlx);
	return (NULL);
}

int	th_listener_start(t_data *scene)
{
	pthread_t	listener;
	
	if (pthread_create(&listener, NULL, &th_listen, scene))
	{
		perror("thread start:");
		rt_shut_down(scene);
		return (1);
	}
	pthread_join(listener, NULL);
	return (0);
}

void	speak(t_data *scene, char *msg);
int	is_printing(t_data *scene)
{
	int i;

	i = -1;
	pthread_mutex_lock(&scene->print);
	if (scene->is_printing == 1)
	{
		speak(scene, "is printing");
		pthread_mutex_unlock(&scene->print);
		return (1);
	}
	pthread_mutex_unlock(&scene->print);
	return (0);	
}

int	all_ready(t_painter *painter);
void	*th_painter_draw(void *worker)
{
	t_painter *painter;
	t_data	*scene;

	painter = (t_painter *)worker;
	scene = painter->sceneref;
	while (!painter->done)
	{
		speak(scene, "thread is painting");
		display_color(scene, painter);

		pthread_mutex_lock(&painter->brush);
		painter->ready = 1;
		speak(scene, "thread is ready");
		pthread_mutex_unlock(&painter->brush);


	//	while (!all_ready(scene->painter))
	//		;
		speak(scene, "all thread are ready");
		while (is_printing(scene))
			;

	//	if (scene->painter_at_rest == THREAD_NB)
	//	{
	//		scene->is_painting = 0;
	//		pthread_cond_signal(&scene->modifyer);
	//	}
	//	printf("thread %d is waiting\n", painter->id);
	//	while (scene->is_painting)
	//		pthread_cond_wait(&scene->brush, &scene->mutex);
	//	pthread_mutex_unlock(&scene->mutex);




//    	scene->painter_ready++;
//        if (scene->painter_ready < THREAD_NB) {
//            pthread_cond_wait(&scene->wait_for_others, &scene->mutex);
//        } else
//		{
//            scene->painter_ready = 0;
//            scene->painter_at_rest = 0;
//            pthread_cond_broadcast(&scene->wait_for_others);
//        }
//		pthread_mutex_unlock(&scene->mutex);
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

	i = -1;
	while (++i < THREAD_NB)
		pthread_join(scene->painter[i].itself, NULL);
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
