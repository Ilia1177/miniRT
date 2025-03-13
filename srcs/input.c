#include <miniRT.h>

int	handle_input(t_data *scene)
{
	(void)scene;
	if (scene->key_state[XK_Left] == 1)
		scene->cam.pos.x -=1;
	if (scene->key_state[XK_Right] == 1)
		scene->cam.pos.x +=1;
	if (scene->key_state[XK_Down] == 1)
		scene->cam.pos.y +=1;
	if (scene->key_state[XK_Up] == 1)
		scene->cam.pos.y +=1;
	/* if (scene->key_state[XK_Escape]) */
	/* 	rt_shut_down(scene); */
	/* if (scene->key_state[XK_a]) */
	/* 	scene->cam.pos.z--; */
	/* if (scene->key_state[XK_w]) */
	/* 	scene->cam.pos.z++; */
	/* if (scene->key_state[XK_d]) */
	/* 	scene->cam.pos.x++; */
	/* if (scene->key_state[XK_s]) */
	/* 	scene->cam.pos.x--; */
	/* if (scene->key_state[XK_t]) */
	/* 	scene->light->intensity += 0.1; */
	/* if (scene->key_state[XK_y]) */
	/* 	scene->light->intensity -= 0.1; */
	/* if (scene->key_state[XK_g]) */
	/* 	scene->sphere->specular += 1; */
	/* if (scene->key_state[XK_h]) */
	/* 	scene->sphere->specular -= 1; */
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

    mouse_move(&scene->cam, delta_x, delta_y);

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
