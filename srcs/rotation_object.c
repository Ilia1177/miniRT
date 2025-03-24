#include <miniRT.h>

void	change_axis(t_object *obj)
{
	t_vec3	new_axis;

	new_axis.x = obj->right.x * obj->axis.x + obj->up.x * obj->axis.y + obj->dir.x * obj->axis.z;
	new_axis.y = obj->right.y * obj->axis.x + obj->up.y * obj->axis.y + obj->dir.y * obj->axis.z;
	new_axis.z = obj->right.z * obj->axis.x + obj->up.z * obj->axis.y + obj->dir.z * obj->axis.z;
	obj->axis = normalize_vec3(new_axis); 
	obj->axis = new_axis;
}

void	rotate(t_object *obj)
{

    const float		rad_yaw = obj->yaw * (M_PI / 180.0f);
    const float		rad_pitch = obj->pitch * (M_PI / 180.0f);
	const t_vec3	world_up = {0, 1, 0, 0};

    obj->dir.x = cos(rad_yaw) * cos(rad_pitch);
    obj->dir.y = sin(rad_pitch);
    obj->dir.z = sin(rad_yaw) * cos(rad_pitch);
    obj->dir = normalize_vec3(obj->dir);
    obj->right = normalize_vec3(cross_vec3(world_up, obj->dir));
    //cam->up = normalize_vec3(cross_vec3(cam->dir, cam->right));
    obj->up = cross_vec3(obj->dir, obj->right);
	change_axis(obj);
	obj->yaw = 0.0f;
	obj->pitch = 0.0f;
}


