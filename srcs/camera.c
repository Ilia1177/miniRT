#include <miniRT.h>

void update_camera_vectors(t_camera *cam)
{
	const float         rad_yaw = cam->yaw * (M_PI / 180.0f);
	const float         rad_pitch = cam->pitch * (M_PI / 180.0f);
		const t_vec3    world_up = {0, 1, 0, 0};
	t_matrix	r;

	r.k.x = cos(rad_yaw) * cos(rad_pitch);
	r.k.y = sin(rad_pitch);
	r.k.z = sin(rad_yaw) * cos(rad_pitch);
	r.k.w = 0;
//	r.k = normalize_vec3(r.k);
	r.i = cross_vec3(world_up, r.k);
	r.j = cross_vec3(r.k, r.i);
	r.p = (t_vec3) {0,0,0,1};
 
	cam->t_m.i = r.i;
	cam->t_m.j = r.j;
	cam->t_m.k = r.k;
	//cam->t_m = mat_compose(cam->t_m, r);
	//cam->t_m = mat_rotate(r, cam->t_m);
//	cam->t_m.k = normalize_vec3(add_vec3(cam->t_m.k, r.k));
//	cam->t_m.i = normalize_vec3(cross_vec3(world_up, cam->t_m.k)); 
//	cam->t_m.j = normalize_vec3(cross_vec3(cam->t_m.k, cam->t_m.i));
	//cam->t_m = mat_compose(cam->t_m, r);
	print_matrix(cam->t_m);
	cam->i_m = mat_inverse(cam->t_m);
}

void	rotate_x(t_camera *cam, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	r;
	const t_vec3 up = {0, 1, 0, 0};
	//r.j = normalize_vec3((t_vec3) {0, cos(theta), sin(theta), 0});
	r.k = normalize_vec3((t_vec3) {0, -sin(theta), cos(theta), 0});
	//r.i = normalize_vec3(cross_vec3(r.j, r.k));	

	r.i = cross_vec3(up, r.k);
	r.j = cross_vec3(r.k, r.i);
	r.p = (t_vec3) {0, 0, 0, 1};

	printf("cam T matrix\n");
	print_matrix(cam->t_m);
	//cam->t_m = mat_compose(r, cam->t_m);
	cam->t_m = mat_rotate(cam->t_m, r);
	printf("cam T composed matrix\n");
	print_matrix(cam->t_m);
	printf("calc camera inverse t\n");
	cam->i_m = mat_inverse(cam->t_m);
	print_matrix(cam->i_m);
}

void	rotate_y(t_camera *cam, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	r;
	const t_vec3 up = {0, 1, 0, 0};

	//r.i = normalize_vec3((t_vec3) {cos(theta), 0, -sin(theta), 0});
	r.k = normalize_vec3((t_vec3) {sin(theta), 0, cos(theta), 0});
	r.i = cross_vec3(up, r.k);
	r.j = cross_vec3(r.k, r.i);
	//r.j = normalize_vec3(cross_vec3(r.k, r.i));
	r.p = (t_vec3) {0, 0, 0, 1};

	//cam->t_m = mat_compose(r , cam->t_m);
	cam->t_m = mat_rotate(cam->t_m, r);
	printf("cam T composed matrix\n");
	print_matrix(cam->t_m);
	printf("calc camera inverse t\n");
	cam->i_m = mat_inverse(cam->t_m);
	print_matrix(cam->i_m);
}

// Calculate viewport width from FOV and focal length
float calc_vp_width(float fov_degrees, float focal_length)
{
	float	vp_width;

	vp_width = 2.0f * focal_length * tan((fov_degrees / 2.0f) * (M_PI / 180.0f));
	return (vp_width);
}
