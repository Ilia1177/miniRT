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

int	handle_input(t_data *scene)
{
	if (scene->key_state[XK_Left] == 1)
		scene->cam.yaw += 5;
	if (scene->key_state[XK_Right] == 1)
		scene->cam.yaw -= 5;
	if (scene->key_state[XK_Down] == 1)
		scene->cam.pitch -= 5;
	if (scene->key_state[XK_Up] == 1)
		scene->cam.pitch += 5;
	if (scene->key_state[XK_w] == 1)
		move_camera_forward(&scene->cam, 0.5);
	if (scene->key_state[XK_s] == 1)
		move_camera_backward(&scene->cam, 0.5);
	if (scene->key_state[XK_a] == 1)
		move_camera_left(&scene->cam, 0.5);
	if (scene->key_state[XK_d] == 1)
		move_camera_right(&scene->cam, 0.5);
	return (0);
}

int	key_press(int keysym, t_data *scene)
{
	printf("key pressed at keysym:%d", keysym);
	if (keysym == XK_Escape)
		rt_shut_down(scene);
	scene->key_state[keysym] = 1;
	return (0);
}

int	key_release(int keysym, t_data *scene)
{
	scene->key_state[keysym] = 0;
	return (0);
}

int	mouse_pos(int x, int y, t_data *scene)
{
	static int last_x = 0;
    static int last_y = 0;
    float delta_x = x - last_x;
    float delta_y = y - last_y;

    //mouse_move(&scene->cam, delta_x, delta_y);
    last_x = x;
    last_y = y;
	scene->mouse.x = x;
	scene->mouse.y = y;
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_data *scene)
{
	(void)keycode;
	scene->mouse.x = x;
	scene->mouse.y = y;
	scene->mouse_state = 1;
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_data *scene)
{
	(void)x;
	(void)y;
	(void)keycode;
	scene->mouse_state = 0;
	return (0);
}
