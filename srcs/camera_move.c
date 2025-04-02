#include <miniRT.h>

void translate_camera_local(t_camera *camera, float dx, float dy, float dz)
{

    // Extract camera's local axes
    t_vec3 right = camera->t_m.i;
    t_vec3 up = camera->t_m.j;
    t_vec3 forward = camera->t_m.k;

    // Compute world-space translation
//    t_vec3 world_move = add_vec3(
//		add_vec3(
//            mult_vec3(right, dx),
//            mult_vec3(up, dy)
//        ),
//        mult_vec3(forward, dz)
//    );
	t_vec3 world_z = mat_apply(camera->t_m, (t_vec3) {0, 0, 1, 0});
	t_vec3 world_x = mat_apply(camera->t_m, (t_vec3) {1, 0, 0, 0});
	t_vec3 world_y = mat_apply(camera->t_m, (t_vec3) {0, 1, 0, 0});
	world_z = mult_vec3(world_z, dz);
	world_x = mult_vec3(world_x, dx);
	world_y = mult_vec3(world_y, dy);
	
	t_vec3 world_move = add_vec3(world_x, add_vec3(world_y, world_z));
	printf("translate: T matrix before\n");
	print_matrix(camera->t_m);

    // Apply translation to camera's position
    camera->t_m.p = add_vec3(camera->t_m.p, world_move);

	printf("translate: T matrix after\n");
	print_matrix(camera->t_m);
    // Update inverse matrix (for ray transformations)
    camera->i_m = mat_inverse(camera->t_m);
	printf("translate: I matrix\n");
	print_matrix(camera->t_m);
}


void move_camera_forward(t_camera *cam, float speed)
{
	translate_camera_local(cam, 0, 0, speed);
//    cam->t_m.p.x += cam->t_m.k.x * speed;
//   cam->t_m.p.y += cam->t_m.k.y * speed;
//  	cam->t_m.p.z += cam->t_m.k.z * speed;
//	printf("cam T matrix\n");
//	print_matrix(cam->t_m);
//	printf("cam inverse matrix\n");
//	print_matrix(cam->i_m);
}

void move_camera_backward(t_camera *cam, float speed)
{
	translate_camera_local(cam, 0, 0, -speed);
//    cam->t_m.p.x -= cam->t_m.k.x * speed;
//    cam->t_m.p.y -= cam->t_m.k.y * speed;
//   	cam->t_m.p.z -= cam->t_m.k.z * speed;
//	cam->i_m = mat_inverse(cam->t_m);
//	printf("cam T matrix\n");
//	print_matrix(cam->t_m);
//	printf("cam inverse matrix\n");
//	print_matrix(cam->i_m);
}

void move_camera_right(t_camera *cam, float speed)
{
	translate_camera_local(cam, speed, 0, 0);

//    cam->t_m.p.x += cam->t_m.i.x * speed;
//	cam->t_m.p.y += cam->t_m.i.y * speed;
//    cam->t_m.p.z += cam->t_m.i.z * speed;
//	cam->i_m = mat_inverse(cam->t_m);
//	printf("cam T matrix\n");
//	print_matrix(cam->t_m);
//	printf("cam inverse matrix\n");
//	print_matrix(cam->i_m);
}

void move_camera_left(t_camera *cam, float speed)
{
	translate_camera_local(cam, -speed, 0, 0);
//    cam->t_m.p.x -= cam->t_m.i.x * speed;
//	cam->t_m.p.y -= cam->t_m.i.y * speed;
//    cam->t_m.p.z -= cam->t_m.i.z * speed;
//	cam->i_m = mat_inverse(cam->t_m);
//	printf("cam T matrix\n");
//	print_matrix(cam->t_m);
//	printf("cam inverse matrix\n");
//	print_matrix(cam->i_m);
}
