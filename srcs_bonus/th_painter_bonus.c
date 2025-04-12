#include <miniRT_bonus.h>

void *th_painter_draw(void *worker)
{
	t_painter *painter;
	t_data	*scene;

	painter = (t_painter *)worker;
	scene = painter->sceneref;
	while (!painter->done)
	{
		printf("thread %d is painting\n", painter->id);
		display_color(scene, painter);
	}
	//mlx_loop(scene->mlx);
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
