#include <miniRT.h>

// not used
t_vec3 compose_quater(t_vec3 after, t_vec3 before)
{
    t_vec3 q;

    q.x = after.w * before.x + after.x * before.w + after.y * before.z - after.z * before.y;
    q.y = after.w * before.y - after.x * before.z + after.y * before.w + after.z * before.x;
    q.z = after.w * before.z + after.x * before.y - after.y * before.x + after.z * before.w;
    q.w = after.w * before.w - after.x * before.x - after.y * before.y - after.z * before.z;

    return q;
}

void	rotate_on_x(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	mat;

	mat.j = (t_vec3) {0, cos(theta), sin(theta), 0};
	mat.k = (t_vec3) {0, -sin(theta), cos(theta), 0};
//	mat.i = normalize_vec3(cross_vec3(obj->up, obj->dir));
	mat.i = (t_vec3) {1, 0, 0, 0};
	mat.p = (t_vec3) {0, 0, 0, 1};
	
	//obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
	obj->i_m = mat_inverse(obj->t_m);
	print_matrix(obj->t_m);
}

void	rotate_on_y(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	mat;

	mat.i = (t_vec3) {cos(theta), 0, -sin(theta), 0};
	mat.k = (t_vec3) {sin(theta), 0, cos(theta), 0};
//	mat.j = normalize_vec3(cross_vec3(mat.k, mat.i));
	mat.j = (t_vec3) {0, 1, 0, 0};
	mat.p = (t_vec3) {0, 0, 0, 1};

	// both are modified because of the use of axis in intersection
//	obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
	obj->i_m = mat_inverse(obj->t_m);
	print_matrix(obj->t_m);
}

void	rotate_on_z(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	mat;

	mat.i = (t_vec3) {cos(theta), sin(theta), 0, 0};
	mat.j = (t_vec3) {-sin(theta), cos(theta), 0, 0};
//	mat.k = normalize_vec3(cross_vec3(mat.i, mat.j));
	mat.k = (t_vec3) {0, 0, 1, 0};
	mat.p = (t_vec3) {0, 0, 0, 1};

	//obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
	obj->i_m = mat_inverse(obj->t_m);
	print_matrix(obj->t_m);
}
