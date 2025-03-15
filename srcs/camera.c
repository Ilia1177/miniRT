#include <miniRT.h>

// Convert yaw & pitch to direction, right, and up vectors
void update_camera_vectors(t_camera *cam)
{
    float rad_yaw = cam->yaw * (M_PI / 180.0f);
    float rad_pitch = cam->pitch * (M_PI / 180.0f);

    // Compute new direction vector
    cam->dir.x = cos(rad_yaw) * cos(rad_pitch);
    cam->dir.y = sin(rad_pitch);
    cam->dir.z = sin(rad_yaw) * cos(rad_pitch);
    cam->dir = normalize_vec3(cam->dir);
	//print_vec3(cam->up, "dir");
	//
	t_vec3 world_up = {0, 1, 0};
    // Compute right vector (always perpendicular to dir and world up)
    cam->right = normalize_vec3(cross_vec3(world_up, cam->dir));
	//print_vec3(cam->up, "right");

    // Compute up vector (perpendicular to dir and right)
    cam->up = cross_vec3(cam->dir, cam->right);
	//print_vec3(cam->up, "up");
}

t_vec3 apply_camera_rotation(t_camera cam, t_vec3 v)
{
	t_vec3 result;
	
	result.x = cam.right.x * v.x + cam.up.x * v.y + cam.dir.x * v.z;
	result.y = cam.right.y * v.x + cam.up.y * v.y + cam.dir.y * v.z;
	result.z = cam.right.z * v.x + cam.up.z * v.y + cam.dir.z * v.z;
    return (result);
}

void mouse_move(t_camera *cam, float delta_x, float delta_y)
{
    float sensitivity = 0.1f; // Adjust for faster/slower rotation

    // Adjust yaw and pitch
    cam->yaw += delta_x * sensitivity;
    cam->pitch -= delta_y * sensitivity; // Invert for correct movement

    // Clamp pitch to avoid flipping (restrict between -89° and 89°)
    if (cam->pitch > 89.0f) cam->pitch = 89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;

    // Update camera vectors based on new angles
    update_camera_vectors(cam);
}


