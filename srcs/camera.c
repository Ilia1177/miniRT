#include <miniRT.h>

void	rotate_x(t_camera *cam, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	r;

//	mat.j = normalize_vec3((t_vec3) {0, cos(theta), sin(theta), 0});
//	mat.k = normalize_vec3((t_vec3) {0, -sin(theta), cos(theta), 0});
	r.j = normalize_vec3((t_vec3) {0, cos(theta), sin(theta), 0});
	r.k = normalize_vec3((t_vec3) {0, -sin(theta), cos(theta), 0});
	r.i = normalize_vec3(cross_vec3(r.j, r.k));
	r.p = (t_vec3) {0, 0, 0, 1};
	
	printf("cam R_x matrix\n");
	print_matrix(r);
	printf("cam T matrix\n");
	print_matrix(cam->t_m);
	cam->t_m = mat_compose(r, cam->t_m);
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

	r.i = normalize_vec3((t_vec3) {cos(theta), 0, -sin(theta), 0});
	r.k = normalize_vec3((t_vec3) {sin(theta), 0, cos(theta), 0});
	r.j = normalize_vec3(cross_vec3(r.k, r.i));
	r.p = (t_vec3) {0, 0, 0, 1};

	printf("cam R_y matrix\n");
	print_matrix(r);
	printf("cam T matrix\n");
	print_matrix(cam->t_m);
	cam->t_m = mat_compose(r, cam->t_m);
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
