#include <miniRT_bonus.h>

void	rotate_camera(t_camera *cam, float dx, float dy, float dz)
{
	(void)dz;
	if (cam->pitch + dx < 80.0f && cam->pitch + dx > -80.0f)
		cam->pitch += dx;
	cam->yaw += dy;
	update_camera_rotation(cam);
	printf("----- CAM matrix yaw: %f, pitch: %f-----\n", cam->yaw, cam->pitch);
	print_mat4(cam->t_m);
}

void	translate_camera(t_camera *camera, float dx, float dy, float dz)
{
	t_vec4	world_x;
	t_vec4	world_y;
	t_vec4	world_z;
	t_vec4	world_move;

	world_x = mult_vec4(mat_apply(camera->t_m, (t_vec4){1, 0, 0, 0}), dx);
	world_y = mult_vec4(mat_apply(camera->t_m, (t_vec4){0, 1, 0, 0}), dy);
	world_z = mult_vec4(mat_apply(camera->t_m, (t_vec4){0, 0, 1, 0}), dz);
	world_move = add_vec4(world_x, add_vec4(world_y, world_z));
    camera->t_m.p = add_vec4(camera->t_m.p, world_move);
    camera->i_m = mat_inverse(camera->t_m);
	printf("---- translate CAM ----\n");
	print_mat4(camera->t_m);
}

void update_camera_rotation(t_camera *cam)
{
	const float         rad_yaw = cam->yaw * (M_PI / 180.0f);
	const float         rad_pitch = cam->pitch * (M_PI / 180.0f);
	const t_vec4		pos = cam->t_m.p;
	t_vec4				dir;

	dir.x = cos(rad_yaw) * cos(rad_pitch);
	dir.y = sin(rad_pitch);
	dir.z = sin(rad_yaw) * cos(rad_pitch);
	dir.w = 0;	
	cam->t_m = mat_orthogonal(normalize_vec4(dir));
	cam->t_m.p = pos;
	cam->i_m = mat_inverse(cam->t_m);
}

void update_camera_rotationi2(t_camera *cam)
{
	const float         rad_yaw = cam->yaw * (M_PI / 180.0f);
	const float         rad_pitch = cam->pitch * (M_PI / 180.0f);
	const t_vec4		world_up = {0, 1, 0, 0};
	t_mat4			r;

	r.k.x = cos(rad_yaw) * cos(rad_pitch);
	r.k.y = sin(rad_pitch);
	r.k.z = sin(rad_yaw) * cos(rad_pitch);
	r.k.w = 0;
	r.k = normalize_vec4(r.k);
	r.i = cross_vec4(world_up, r.k);
	r.j = cross_vec4(r.k, r.i);
 
	cam->t_m.i = r.i;
	cam->t_m.j = r.j;
	cam->t_m.k = r.k;
	cam->i_m = mat_inverse(cam->t_m);
}

// Calculate viewport width from FOV and focal length
float calc_vp_width(float fov_degrees, float focal_length)
{
	float	vp_width;

	vp_width = 2.0f * focal_length * tan((fov_degrees / 2.0f) * (M_PI / 180.0f));
	return (vp_width);
}
