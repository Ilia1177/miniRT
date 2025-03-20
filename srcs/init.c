#include <miniRT.h>

int	scene_init(t_data *scene)
{
	scene->res = 5;
	scene->cam.pos =	(t_vec3) {0, 0, 0};
	scene->cam.dir =	(t_vec3) {0, 0, 1};
	scene->cam.up =		(t_vec3) {0, 1, 0};
	scene->cam.right =	(t_vec3) {1, 0, 0};
	scene->cam.yaw =	90.0f;
	scene->cam.pitch =	0.0f;

	scene->cnv.w = WIDTH;
	scene->cnv.h = HEIGHT;
	//scene->viewport.pos = (t_vec3) {1, 1, 1};
	scene->viewport.h = 1;
	scene->viewport.w = 1;
	//scene->viewport.w = calc_vp_width(70.0f, 1.0);

//	scene->objects = malloc(sizeof(t_object) * 1);
//	scene->objects->type = SPHERE;
//	scene->objects->radius = 100;
//	scene->objects->pos = (t_vec3) {0, 0, 0};
//	scene->objects->orientation = (t_vec3) {0, 1, 0};
//	scene->objects->color = (t_argb) {255, 100, 55, 155};
//	scene->objects->spec = -1;
//	scene->objects->reflect = (t_argb) {0, 0, 0, 0};
//	scene->objects->next = NULL; 
scene->objects = malloc(sizeof(t_object) * 1);
scene->objects->type = PLANE;
scene->objects->radius = 1000;
scene->objects->pos = (t_vec3) {0,-2, 0};
scene->objects->orientation = (t_vec3) {0, 1, 0};
scene->objects->color = (t_argb) {255, 100, 55, 155};
scene->objects->spec = -1;
scene->objects->reflect = (t_argb) {0, 127, 127, 0};
scene->objects->next = NULL; 
scene->objects->next = malloc(sizeof(t_object) * 1);
scene->objects->next->type = SPHERE;
scene->objects->next->radius = 100;
scene->objects->next->pos = (t_vec3) {0, 102, 2};
scene->objects->next->orientation = (t_vec3) {1, 0, 0};
scene->objects->next->height = 10;
scene->objects->next->color = (t_argb) {255, 0, 39, 255};
scene->objects->next->spec = -1;
scene->objects->next->reflect = (t_argb) {0, 127, 127, 127};
scene->objects->next->next = NULL;
scene->lights = malloc(sizeof(t_light) * 1);
scene->lights->type = POINT;
scene->lights->intensity = (t_argb) {255, 200, 200, 200};
scene->lights->dir = (t_vec3) {2, 2, 6};
scene->lights->pos = (t_vec3) {-2, 4, 0};
scene->lights->next = NULL;
scene->lights->next = malloc(sizeof(t_light) * 1);
scene->lights->next->type = AMBIENT;
scene->lights->next->intensity = (t_argb) {255, 55, 55, 55};
scene->lights->next->pos = (t_vec3) {-4, 2, 2};
scene->lights->next->next = NULL; 
	return (0);
}
