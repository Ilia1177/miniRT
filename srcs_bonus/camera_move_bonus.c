#include <miniRT_bonus.h>

void translate_camera(t_camera *camera, float dx, float dy, float dz)
{
	t_vec4	world_x;
	t_vec4	world_y;
	t_vec4	world_z;
	t_vec4	world_move;

	world_x = mult_vec4(mat_apply(camera->t_m, (t_vec4) {1, 0, 0, 0}), dx);
	world_y = mult_vec4(mat_apply(camera->t_m, (t_vec4) {0, 1, 0, 0}), dy);
	world_z = mult_vec4(mat_apply(camera->t_m, (t_vec4) {0, 0, 1, 0}), dz);
	world_move = add_vec4(world_x, add_vec4(world_y, world_z));
    camera->t_m.p = add_vec4(camera->t_m.p, world_move);
    camera->i_m = mat_inverse(camera->t_m);
	printf("---- translate CAM ----\n");
	print_matrix(camera->t_m);
}
