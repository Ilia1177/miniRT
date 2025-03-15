#include <miniRT.h>

int	scene_init(t_data *scene)
{
	scene->cam.pos =	(t_vec3) {0, 0, 0};
	scene->cam.dir =	(t_vec3) {0, 0, 1};
	scene->cam.up =		(t_vec3) {0, 1, 0};
	scene->cam.right =	(t_vec3) {1, 0, 0};
	scene->cam.yaw =	90.0f;
	scene->cam.pitch =	0.0f;



	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	scene->viewport.pos = (t_vec3) {1, 1, 1};
	scene->viewport.h = 1;
	scene->viewport.w = 1;	
	scene->objects = malloc(sizeof(t_object) * 1);
	scene->objects->type = PLANE;
	scene->objects->radius = 1;
	scene->objects->height = 3;
	scene->objects->pos = (t_vec3) {0,-1,-10};
	scene->objects->orientation = (t_vec3) {0, 1, 0};
	scene->objects->color = (t_argb) {255, 20, 127, 200};
	scene->objects->specular = 500;
	scene->objects->reflective = (t_argb) {127, 0, 124, 124};
	scene->objects->next = NULL; 
	scene->objects->next = malloc(sizeof(t_object) * 1);
	scene->objects->next->type = SPHERE;
	scene->objects->next->radius = 1;
	scene->objects->next->pos = (t_vec3) {-2, 0, 5};
	scene->objects->next->color = (t_argb) {255, 85, 189, 32};
	scene->objects->next->specular = 500;
	scene->objects->next->reflective = (t_argb) {0, 0, 0, 0};
	scene->objects->next->next = NULL;
	scene->objects->next->next = malloc(sizeof(t_object) * 1);
	scene->objects->next->next->type = CYLINDER;
	scene->objects->next->next->radius = 0.5;
	scene->objects->next->next->pos = (t_vec3) {1, -1, 5};
	scene->objects->next->next->orientation = (t_vec3) {0, 1, 0};
	scene->objects->next->next->height = 2;
	scene->objects->next->next->color = (t_argb) {255, 54, 36, 89};
	scene->objects->next->next->specular = 500;
	scene->objects->next->next->reflective = (t_argb) {0, 0, 0, 0};
	scene->objects->next->next->next = NULL;
	scene->objects->next->next->next = malloc(sizeof(t_object) * 1);
	scene->objects->next->next->next->type = CYLINDER;
	scene->objects->next->next->next->radius = 0.6;
	scene->objects->next->next->next->pos = (t_vec3) {-1, 1, 5};
	scene->objects->next->next->next->orientation = (t_vec3) {1, 1, 1};
	scene->objects->next->next->next->height = 4;
	scene->objects->next->next->next->color = (t_argb) {255, 0, 241, 127};
	scene->objects->next->next->next->specular = -1;
	scene->objects->next->next->next->reflective = (t_argb) {255, 127, 43, 12};
	scene->objects->next->next->next->next = NULL;
	scene->objects->next->next->next->next = malloc(sizeof(t_object) * 1);
	scene->objects->next->next->next->next->type = SPHERE;
	scene->objects->next->next->next->next->radius = 1;
	scene->objects->next->next->next->next->pos = (t_vec3) {12, 10, 30};
	scene->objects->next->next->next->next->orientation = (t_vec3) {0, 1, 0}; 
	scene->objects->next->next->next->next->height = 2;
	scene->objects->next->next->next->next->color = (t_argb) {255, 124, 25, 69};
	scene->objects->next->next->next->next->specular = -1;
	scene->objects->next->next->next->next->reflective = (t_argb) {255, 85, 13, 5};
	scene->objects->next->next->next->next->next = NULL;
	scene->objects->next->next->next->next->next = malloc(sizeof(t_object) * 1);
	scene->objects->next->next->next->next->next->type = SPHERE;
	scene->objects->next->next->next->next->next->radius = 0.2f;
	scene->objects->next->next->next->next->next->pos = (t_vec3) {0, -0.7, 2.4};
	scene->objects->next->next->next->next->next->orientation = (t_vec3) {0, 1, 0}; 
	scene->objects->next->next->next->next->next->height = 2;
	scene->objects->next->next->next->next->next->color = (t_argb) {255, 10, 52, 69};
	scene->objects->next->next->next->next->next->specular = 5000;
	scene->objects->next->next->next->next->next->reflective = (t_argb) {0, 8, 10, 10};
	scene->objects->next->next->next->next->next->next = NULL;
	scene->lights = malloc(sizeof(t_light) * 1);
	scene->lights->type = DIRECTIONAL;
	scene->lights->intensity = (t_argb) {255, 255, 255, 255};
	scene->lights->dir = (t_vec3) {2, 2, -2};
	scene->lights->pos = (t_vec3) {2, 2, 1};
	scene->lights->next = NULL;
	scene->lights->next = malloc(sizeof(t_light) * 1);
	scene->lights->next->type = DIRECTIONAL;
	scene->lights->next->intensity = (t_argb) {255, 255, 255, 255};
	scene->lights->next->dir = (t_vec3) {-2, 2, -2};
	scene->lights->next->next = NULL;
	/* scene->lights->next->next = malloc(sizeof(t_light) * 1); */
	/* scene->lights->next->next->type = POINT; */
	/* scene->lights->next->next->intensity = (t_argb){0, 0, 0, 0}; */
	/* scene->lights->next->next->pos.x = 2; */
	/* scene->lights->next->next->pos.y = 2; */
	/* scene->lights->next->next->pos.z = 1; */
	/* scene->lights->next->next->next = NULL; */
	return (0);
}
