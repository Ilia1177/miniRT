#include <miniRT.h>

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

//t_matrix	mat_make_rotation(float rx, float ry, t_matrix mat)
//{
	
//}
void	rotate_on_x(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	mat;

	mat.j = (t_vec4) {0, cos(theta), sin(theta), 0};
	mat.k = (t_vec4) {0, -sin(theta), cos(theta), 0};
//	mat.i = normalize_vec4(cross_vec4(obj->up, obj->dir));
	mat.i = (t_vec4) {1, 0, 0, 0};
	mat.p = (t_vec4) {0, 0, 0, 1};
	
	//obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
	obj->i_m = mat_inverse(obj->t_m);
	print_matrix(obj->t_m);
}

void	rotate_on_y(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);
	t_matrix	mat;

	mat.i = (t_vec4) {cos(theta), 0, -sin(theta), 0};
	mat.k = (t_vec4) {sin(theta), 0, cos(theta), 0};
//	mat.j = normalize_vec4(cross_vec4(mat.k, mat.i));
	mat.j = (t_vec4) {0, 1, 0, 0};
	mat.p = (t_vec4) {0, 0, 0, 1};

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

	mat.i = (t_vec4) {cos(theta), sin(theta), 0, 0};
	mat.j = (t_vec4) {-sin(theta), cos(theta), 0, 0};
//	mat.k = normalize_vec4(cross_vec4(mat.i, mat.j));
	mat.k = (t_vec4) {0, 0, 1, 0};
	mat.p = (t_vec4) {0, 0, 0, 1};

	//obj->axis = mat_apply(mat, obj->axis);
	obj->t_m = mat_compose(mat, obj->t_m);
	obj->i_m = mat_inverse(obj->t_m);
	print_matrix(obj->t_m);
}
