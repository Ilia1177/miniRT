#include <miniRT.h>

int	scene_init(t_data *scene)
{
	scene->cam.pos = (t_vec3){0, 0, 0};
	scene->cam.dir = (t_vec3){0, 0, 1};
	scene->cam.up =	(t_vec3){0, 1, 0};
	scene->cam.right = (t_vec3){1, 0, 0};
	
	scene->cam.yaw =	89.0f;
	scene->cam.pitch =	0.0f;
	
	scene->viewport.h = 1; 
	scene->viewport.w = 1; 
	scene->viewport.pos =  (t_vec3){1, 1 ,1};

	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->objects = NULL;

	scene->lights = malloc(sizeof(t_light) * 1);
	scene->lights->type = DIRECTIONAL;
	scene->lights->intensity = 0.3f;
	scene->lights->dir.x = -2;
	scene->lights->dir.y = 0;
	scene->lights->dir.z = -2;
	scene->lights->next = NULL;
	scene->lights->next = malloc(sizeof(t_light) * 1);
	scene->lights->next->type = AMBIENT;
	scene->lights->next->intensity = 0.5;
	scene->lights->next->dir.x = 2;
	scene->lights->next->dir.y = 2;
	scene->lights->next->dir.z = 2;
	scene->lights->next->next = malloc(sizeof(t_light) * 1);
	scene->lights->next->next->type = POINT;
	scene->lights->next->next->intensity = 0.5;
	scene->lights->next->next->pos.x = 2;
	scene->lights->next->next->pos.y = 2;
	scene->lights->next->next->pos.z = 6;
	scene->lights->next->next->next = NULL;

	//printf("objects: %p, objects->next: %p\n", scene->objects, scene->objects->next);
	return (0);
}
