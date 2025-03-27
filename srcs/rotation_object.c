#include <miniRT.h>

t_vec3 compose_quater(t_vec3 after, t_vec3 before)
{
    t_vec3 q;

    q.x = after.w * before.x + after.x * before.w + after.y * before.z - after.z * before.y;
    q.y = after.w * before.y - after.x * before.z + after.y * before.w + after.z * before.x;
    q.z = after.w * before.z + after.x * before.y - after.y * before.x + after.z * before.w;
    q.w = after.w * before.w - after.x * before.x - after.y * before.y - after.z * before.z;

    return q;
}

void	change_axis(t_object *obj)
{
	t_vec3	new_axis;

	new_axis.x = obj->right.x * obj->axis.x + obj->up.x * obj->axis.y + obj->dir.x * obj->axis.z;
	new_axis.y = obj->right.y * obj->axis.x + obj->up.y * obj->axis.y + obj->dir.y * obj->axis.z;
	new_axis.z = obj->right.z * obj->axis.x + obj->up.z * obj->axis.y + obj->dir.z * obj->axis.z;
	obj->axis = normalize_vec3(new_axis); 
	//obj->axis = new_axis;
}

void	rotate_on_x(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);

	//obj->right = (t_vec3) {1, 0 ,0, 0};
	obj->up = (t_vec3) {0, cos(theta), sin(theta), 0};
	obj->dir = (t_vec3) {0, -sin(theta), cos(theta), 0};
	obj->right = normalize_vec3(cross_vec3(obj->up, obj->dir));
	change_axis(obj);
}

void	rotate_on_y(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);

	obj->right = (t_vec3) {cos(theta), 0 , -sin(theta), 0};
	//obj->up = (t_vec3) {0, 1, 0, 0};
	obj->dir = (t_vec3) {sin(theta), 0, cos(theta), 0};
	obj->up = normalize_vec3(cross_vec3(obj->dir, obj->right));
	change_axis(obj);
}

void	rotate_on_z(t_object *obj, float theta)
{
	theta = theta * (M_PI / 180.0f);

	obj->right = (t_vec3) {cos(theta), sin(theta),0 , 0};
	obj->up = (t_vec3) {-sin(theta), cos(theta), 0, 0};
//	obj->dir = (t_vec3) {0, 0, 1, 0};
	obj->dir = normalize_vec3(cross_vec3(obj->right, obj->up));
	change_axis(obj);
}




//void	rotate(t_object *obj) //float yaw, float pitch, float roll)
//{

  //  const float		rad_yaw = obj->yaw * (M_PI / 180.0f);
 //   const float		rad_pitch = obj->pitch * (M_PI / 180.0f);
   // const float		rad_roll = roll * (M_PI / 180.0f);
//	const t_vec3	world_up = {0, 1, 0, 0};


//    obj->dir.x = cos(rad_yaw) * cos(rad_pitch);
//    obj->dir.y = sin(rad_pitch);
//    obj->dir.z = sin(rad_yaw) * cos(rad_pitch);
//    obj->dir = normalize_vec3(obj->dir);
//    obj->right = normalize_vec3(cross_vec3(world_up, obj->dir));
//    //cam->up = normalize_vec3(cross_vec3(cam->dir, cam->right));
//    obj->up = cross_vec3(obj->dir, obj->right);
//	change_axis(obj);
//	obj->yaw = 0.0f;
//	obj->pitch = 0.0f;
	//}


