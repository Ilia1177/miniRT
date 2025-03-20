#include <miniRT.h>

// Convert yaw & pitch to direction, right, and up vectors
// Compute new direction vector
// Compute right vector (always perpendicular to dir and world up)
// Compute up vector (perpendicular to dir and right)
void update_camera_vectors(t_camera *cam)
{
    const float		rad_yaw = cam->yaw * (M_PI / 180.0f);
    const float		rad_pitch = cam->pitch * (M_PI / 180.0f);
	const t_vec3	world_up = {0, 1, 0};

    cam->dir.x = cos(rad_yaw) * cos(rad_pitch);
    cam->dir.y = sin(rad_pitch);
    cam->dir.z = sin(rad_yaw) * cos(rad_pitch);
    cam->dir = normalize_vec3(cam->dir);
    cam->right = normalize_vec3(cross_vec3(world_up, cam->dir));
    //cam->up = normalize_vec3(cross_vec3(cam->dir, cam->right));
    cam->up = cross_vec3(cam->dir, cam->right);
}

t_vec3 apply_camera_rotation(t_camera cam, t_vec3 v)
{
	t_vec3 result;
	
	result.x = cam.right.x * v.x + cam.up.x * v.y + cam.dir.x * v.z;
	result.y = cam.right.y * v.x + cam.up.y * v.y + cam.dir.y * v.z;
	result.z = cam.right.z * v.x + cam.up.z * v.y + cam.dir.z * v.z;
    return (result);
}

// Adjust yaw and pitch
// Clamp pitch to avoid flipping (restrict between -89° and 89°)
// Invert for correct movement
// Update camera vectors based on new angles
void mouse_move(t_camera *cam, float delta_x, float delta_y)
{
    const float	sensitivity = MOUSE_SENSITIVITY; // Adjust for faster/slower rotation

    cam->yaw += delta_x * sensitivity;
    cam->pitch -= delta_y * sensitivity;
    if (cam->pitch > 89.0f)
	{
	   	cam->pitch = 89.0f;
		return ;
	}
    if (cam->pitch < -89.0f)
	{
	   	cam->pitch = -89.0f;
		return ;
	}
    update_camera_vectors(cam);
}

// Calculate viewport width from FOV and focal length
float calc_vp_width(float fov_degrees, float focal_length)
{
	float	vp_width;

	vp_width = 2.0f * focal_length * tan((fov_degrees / 2.0f) * (M_PI / 180.0f));
	return (vp_width);
}
