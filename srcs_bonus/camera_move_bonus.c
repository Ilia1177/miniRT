#include <miniRT_bonus.h>

void translate_camera(t_camera *camera, float dx, float dy, float dz)
{
	t_vec3	world_x;
	t_vec3	world_y;
	t_vec3	world_z;
	t_vec3	world_move;

	world_x = mult_vec3(mat_apply(camera->t_m, (t_vec3) {1, 0, 0, 0}), dx);
	world_y = mult_vec3(mat_apply(camera->t_m, (t_vec3) {0, 1, 0, 0}), dy);
	world_z = mult_vec3(mat_apply(camera->t_m, (t_vec3) {0, 0, 1, 0}), dz);
	world_move = add_vec3(world_x, add_vec3(world_y, world_z));
    camera->t_m.p = add_vec3(camera->t_m.p, world_move);
    camera->i_m = mat_inverse(camera->t_m);
}
