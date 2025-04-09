#include <miniRT_bonus.h>

void update_camera_rotation(t_camera *cam)
{
	const float         rad_yaw = cam->yaw * (M_PI / 180.0f);
	const float         rad_pitch = cam->pitch * (M_PI / 180.0f);
	const t_vec4		world_up = {0, 1, 0, 0};
	t_matrix			r;

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

//NOT USED !!
void	rotate_x(t_camera *cam, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	r;
	//const t_vec4 up = {0, 1, 0, 0};
	r.j = normalize_vec4((t_vec4) {0, cos(theta), sin(theta), 0});
	r.k = normalize_vec4((t_vec4) {0, -sin(theta), cos(theta), 0});
	r.i = normalize_vec4(cross_vec4(r.j, r.k));	

	//r.i = cross_vec4(up, r.k);
	//r.j = cross_vec4(r.k, r.i);
	r.p = (t_vec4) {0, 0, 0, 1};

	printf("cam T initial transformation matrix\n");
	print_matrix(cam->t_m);
	cam->t_m = mat_compose(r, cam->t_m);
	//cam->t_m = mat_rotate(cam->t_m, r);
	printf("cam T composed matrix\n");
	print_matrix(cam->t_m);
	printf("calc camera inverse t\n");
	cam->i_m = mat_inverse(cam->t_m);
	print_matrix(cam->i_m);
}

//NOT USED !!
void	rotate_y(t_camera *cam, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	r;
	//const t_vec4 up = {0, 1, 0, 0};

	r.i = normalize_vec4((t_vec4) {cos(theta), 0, -sin(theta), 0});
	r.k = normalize_vec4((t_vec4) {sin(theta), 0, cos(theta), 0});
	//r.i = cross_vec4(up, r.k);
	r.j = cross_vec4(r.k, r.i);
	//r.j = normalize_vec4(cross_vec4(r.k, r.i));
	r.p = (t_vec4) {0, 0, 0, 1};

	cam->t_m = mat_compose(r , cam->t_m);
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
