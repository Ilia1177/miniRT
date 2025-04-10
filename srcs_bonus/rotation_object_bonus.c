#include <miniRT_bonus.h>

// not used
t_vec4 compose_quater(t_vec4 after, t_vec4 before)
{
    t_vec4 q;

    q.x = after.w * before.x + after.x * before.w + after.y * before.z - after.z * before.y;
    q.y = after.w * before.y - after.x * before.z + after.y * before.w + after.z * before.x;
    q.z = after.w * before.z + after.x * before.y - after.y * before.x + after.z * before.w;
    q.w = after.w * before.w - after.x * before.x - after.y * before.y - after.z * before.z;

    return q;
}

void	rotate_on_x(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_mat4	mat;

	mat.j = (t_vec4) {0, cos(theta), sin(theta), 0};
	mat.k = (t_vec4) {0, -sin(theta), cos(theta), 0};
//	mat.i = normalize_vec4(cross_vec4(obj->up, obj->dir));
	mat.i = (t_vec4) {1, 0, 0, 0};
	mat.p = obj->t_m.p;
	
	//obj->t_m = mat_compose(mat, obj->t_m);
	obj->t_m = mat;
	obj->i_m = mat_inverse(obj->t_m);
}

void	rotate_on_y(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_mat4	mat;

	mat.i = (t_vec4) {cos(theta), 0, -sin(theta), 0};
	mat.k = (t_vec4) {sin(theta), 0, cos(theta), 0};
//	mat.j = normalize_vec4(cross_vec4(mat.k, mat.i));
	mat.j = (t_vec4) {0, 1, 0, 0};
	mat.p = obj->t_m.p;

	// both are modified because of the use of axis in intersection
//	obj->axis = mat_apply(mat, obj->axis);
	//obj->t_m = mat_compose(mat, obj->t_m);
	
	obj->t_m = mat;
	obj->i_m = mat_inverse(obj->t_m);
	print_mat4(obj->t_m);
}

void	rotate_on_z(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_mat4	mat;

	mat.i = (t_vec4) {cos(theta), sin(theta), 0, 0};
	mat.j = (t_vec4) {-sin(theta), cos(theta), 0, 0};
//	mat.k = normalize_vec4(cross_vec4(mat.i, mat.j));
	mat.k = (t_vec4) {0, 0, 1, 0};
	mat.p = obj->t_m.p;

	//obj->axis = mat_apply(mat, obj->axis);
	//obj->t_m = mat_compose(mat, obj->t_m);
	obj->t_m = mat;
	obj->i_m = mat_inverse(obj->t_m);
	print_mat4(obj->t_m);
}
