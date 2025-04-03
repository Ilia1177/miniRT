#include <miniRT.h>
void rotate_x(t_camera *cam, float theta) {
    theta = theta * (M_PI / 180.0f); // Convert degrees to radians

    // Extract the camera's current basis vectors and position
    t_vec3 i = cam->t_m.i;
    t_vec3 j = cam->t_m.j;
    t_vec3 k = cam->t_m.k;
    t_vec3 position = cam->t_m.p; // Preserve the original position

    // Rotate the j and k vectors around the camera's local X-axis (i)
    t_vec3 new_j = add_vec3(mult_vec3(j, cos(theta)), mult_vec3(k, sin(theta)));
    t_vec3 new_k = add_vec3(mult_vec3(j, -sin(theta)), mult_vec3(k, cos(theta)));

    // Normalize and orthogonalize the new basis vectors
    new_j = normalize_vec3(new_j);
    new_k = normalize_vec3(new_k);
    i = cross_vec3(new_j, new_k); // Recompute i to ensure orthogonality
    i = normalize_vec3(i);

    // Update the camera's transformation matrix with the new orientation
    cam->t_m.i = i;
    cam->t_m.j = new_j;
    cam->t_m.k = new_k;
    cam->t_m.p = position; // Keep the original position unchanged

    // Update the inverse matrix (view matrix)
    cam->i_m = mat_inverse(cam->t_m);
}

void rotate_y(t_camera *cam, float theta) {
    theta = theta * (M_PI / 180.0f); // Convert degrees to radians

    // Extract the camera's current basis vectors and position
    t_vec3 i = cam->t_m.i;
    t_vec3 j = cam->t_m.j;
    t_vec3 k = cam->t_m.k;
    t_vec3 position = cam->t_m.p; // Preserve the original position


    // Rotate the i and k vectors around the camera's local X-axis (j)
    t_vec3 new_i = add_vec3(mult_vec3(i, cos(theta)), mult_vec3(k, -sin(theta)));
    t_vec3 new_k = add_vec3(mult_vec3(i, sin(theta)), mult_vec3(k, cos(theta)));

    // Normalize and orthogonalize the new basis vectors
    new_i = normalize_vec3(new_i);
    new_k = normalize_vec3(new_k);
    j = cross_vec3(new_k, new_i ); // Recompute j to ensure orthogonality
    j = normalize_vec3(j);

    // Update the camera's transformation matrix with the new orientation
    cam->t_m.j = j;
    cam->t_m.i = new_i;
    cam->t_m.k = new_k;
    cam->t_m.p = position; // Keep the original position unchanged

    // Update the inverse matrix (view matrix)
    cam->i_m = mat_inverse(cam->t_m);
}




void	rotate_x_SAVE(t_camera *cam, float theta)
{
//	cam->yaw += theta;
	theta = theta * (M_PI / 180.0f);
	t_matrix	r;

	r.j = normalize_vec3((t_vec3) {0, cos(theta), sin(theta), 0});
	r.k = normalize_vec3((t_vec3) {0, -sin(theta), cos(theta), 0});
	r.i = normalize_vec3(cross_vec3(r.j, r.k));
	r.p = (t_vec3) {0, 0, 0, 1};

	printf("cam R_x matrix\n");
	print_matrix(r);
	printf("cam T matrix\n");
	print_matrix(cam->t_m);
	//cam->t_m = mat_compose(cam->t_m, r);
	cam->t_m = mat_rotate(cam->t_m, r);
	printf("cam T composed matrix\n");
	print_matrix(cam->t_m);
	printf("calc camera inverse t\n");
	cam->i_m = mat_inverse(cam->t_m);
	print_matrix(cam->i_m);
}

void	rotate_y_SAVE(t_camera *cam, float theta)
{
//	if (cam->pitch < 90.0f)
//		cam->pitch -= theta;
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

	//cam->t_m = mat_compose(cam->t_m, r);
	cam->t_m = mat_rotate(cam->t_m, r);
	printf("cam T composed matrix\n");
	print_matrix(cam->t_m);
	printf("calc camera inverse t\n");
	cam->i_m = mat_inverse(cam->t_m);
	print_matrix(cam->i_m);
}

// Convert yaw & pitch to direction, right, and up vectors
// Compute new direction vector
// Compute right vector (always perpendicular to dir and world up)
// Compute up vector (perpendicular to dir and right)
void update_camera_vectors(t_camera *cam)
{
	rotate_y(cam, 0);
	rotate_x(cam, 0);
//    const float         rad_yaw = cam->yaw * (M_PI / 180.0f);
//    const float         rad_pitch = cam->pitch * (M_PI / 180.0f);
//	const t_vec3		world_up = {0, 1, 0, 0};
//
//    cam->t_m.k.x = cos(rad_yaw) * cos(rad_pitch);
//    cam->t_m.k.y = sin(rad_pitch);
//    cam->t_m.k.z = sin(rad_yaw) * cos(rad_pitch);
//    cam->t_m.k = normalize_vec3(cam->t_m.k);
//    cam->t_m.i = normalize_vec3(cross_vec3(world_up, cam->t_m.k));
//    //cam->up = normalize_vec3(cross_vec3(cam->dir, cam->right));
//    cam->t_m.j = cross_vec3(cam->t_m.k, cam->t_m.i);
//
//	printf("TRANSFORM MATRIX:\n");
//	printf("cam YAW: %f ", cam->yaw);
//	printf("cam PITCH: %f\n", cam->pitch);
//	print_matrix(cam->t_m);
//	cam->i_m = mat_inverse(cam->t_m);
}

// Calculate viewport width from FOV and focal length
float calc_vp_width(float fov_degrees, float focal_length)
{
	float	vp_width;

	vp_width = 2.0f * focal_length * tan((fov_degrees / 2.0f) * (M_PI / 180.0f));
	return (vp_width);
}
