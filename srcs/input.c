#include <miniRT.h>

int	handle_input(t_data *scene)
{
	if (scene->key_state[XK_Escape])
		rt_shut_down(scene);
	if (scene->key_state[XK_a])
		scene->cam.x--;
	if (scene->key_state[XK_w])
		scene->cam.y--;
	if (scene->key_state[XK_d])
		scene->cam.x++;
	if (scene->key_state[XK_s])
		scene->cam.y++;
	return (0);
}

int	key_press(int keycode, t_data *scene)
{
	if (keycode >= 0 && keycode < 99999)
		scene->key_state[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *scene)
{
	if (keycode >= 0 && keycode < 99999)
		scene->key_state[keycode] = 0;
	return (0);
}

int	mouse_pos(int x, int y, t_data *scene)
{
	(void)scene;
	scene->mouse.x = x;
	scene->mouse.y = y;
	printf("Mouse moved to: (%d, %d)\n", x, y);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_data *scene)
{
	(void)keycode;
	scene->mouse.x = x;
	scene->mouse.y = y;
	scene->mouse_state = 1;
	ft_printf("mouse pressed at x:%d, y:%d\n", x, y);
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
