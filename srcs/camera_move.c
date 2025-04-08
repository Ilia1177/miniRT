#include <miniRT.h>

void move_camera_forward(t_camera *cam, float speed)
{
    cam->pos.x += cam->dir.x * speed;
    cam->pos.y += cam->dir.y * speed;
    cam->pos.z += cam->dir.z * speed;
}

void move_camera_backward(t_camera *cam, float speed)
{
    cam->pos.x -= cam->dir.x * speed;
    cam->pos.y -= cam->dir.y * speed;
    cam->pos.z -= cam->dir.z * speed;
}

void move_camera_right(t_camera *cam, float speed)
{
    cam->pos.x += cam->right.x * speed;
    cam->pos.y += cam->right.y * speed;
    cam->pos.z += cam->right.z * speed;
}

void move_camera_left(t_camera *cam, float speed)
{
    cam->pos.x -= cam->right.x * speed;
    cam->pos.y -= cam->right.y * speed;
    cam->pos.z -= cam->right.z * speed;
}
