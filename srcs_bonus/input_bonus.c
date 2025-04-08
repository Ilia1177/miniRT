#include <miniRT_bonus.h>

// translate object on z axis zith i and j
void	handle_object_translation(t_data *scene)
{
	if (scene->key_state[XK_i] == 1 && scene->selected)
		scene->selected->t_m.p.z += 0.1;
	if (scene->key_state[XK_k] == 1 && scene->selected)
		scene->selected->t_m.p.z -= 0.1;
	if (scene->key_state[XK_l] == 1 && scene->selected)
		scene->selected->t_m.p.x += 0.1;
	if (scene->key_state[XK_j] == 1 && scene->selected)
		scene->selected->t_m.p.x -= 0.1;
	if (scene->key_state[XK_u] == 1 && scene->selected)
		scene->selected->t_m.p.y += 0.1;
	if (scene->key_state[XK_o] == 1 && scene->selected)
		scene->selected->t_m.p.y -= 0.1;
}

void	handle_object_rotation(t_data *scene)
{
	if (scene->key_state[XK_z] == 1 && scene->selected)
		rotate_on_x(scene->selected, 1.0f);
	if (scene->key_state[XK_x] == 1 && scene->selected)
		rotate_on_y(scene->selected, 1.0f);
	if (scene->key_state[XK_c] == 1 && scene->selected)
		rotate_on_z(scene->selected, 1.0f);
}

void	handle_camera_move(t_data *scene)
{
	if (scene->key_state[XK_Left] == 1) 
		scene->cam.yaw++;
	if (scene->key_state[XK_Right] == 1)
		scene->cam.yaw--;
	if (scene->key_state[XK_Down] == 1 && scene->cam.pitch < 89.0f)
		scene->cam.pitch--;
	if (scene->key_state[XK_Up] == 1 && scene->cam.pitch > -89.0f)
		scene->cam.pitch++;
	if (scene->key_state[XK_w] == 1)
		translate_camera(&scene->cam, 0, 0, 0.5f);
	if (scene->key_state[XK_s] == 1)
		translate_camera(&scene->cam, 0, 0, -0.5f);
	if (scene->key_state[XK_a] == 1)
		translate_camera(&scene->cam, -0.5f, 0, 0);
	if (scene->key_state[XK_d] == 1)
		translate_camera(&scene->cam, 0.5f, 0, 0);
}

int	handle_input(t_data *scene)
{
	handle_object_translation(scene);
	handle_object_rotation(scene);
	handle_camera_move(scene);
	if (scene->key_state[XK_space] == 1)
		save_as_ppm(&scene->img, "img.ppm");
	if (scene->key_state[XK_F1] == 1 && scene->res < 10)
		scene->res++;
	if (scene->key_state[XK_F2] == 1 && scene->res > 1)
		scene->res--;
	return (0);
}

int	key_press(int keysym, t_data *scene)
{
	scene->rend = 1;
	if (keysym == XK_Escape)
		rt_shut_down(scene);
	else if (keysym > 0 && keysym < 99999)
		scene->key_state[keysym] = 1;
	return (keysym);
}

int	key_release(int keysym, t_data *scene)
{
	//scene->rend = 0;
	if (keysym > 0 && keysym < 99999)
		scene->key_state[keysym] = 0;
	return (0);
}

int	mouse_pos(int x, int y, t_data *scene)
{
	static int last_x = 0;
    static int last_y = 0;
    //float delta_x = x - last_x;
    //float delta_y = y - last_y;
	(void)scene;
 //   mouse_move(&scene->cam, delta_x, delta_y);
    last_x = x;
    last_y = y;
//	scene->mouse.x = x;
//	scene->mouse.y = y;
	return (0);
}

void	select_object(t_data *scene)
{
	t_ray		catch_ray;
	t_canvas	cnv;
	t_viewport  vp;
	t_object	*obj;
	static t_argb last_color;

	obj = scene->selected;
	vp = scene->viewport;
	cnv = scene->cnv;
	cnv.loc.x = scene->mouse.x - (cnv.w / 2);
	cnv.loc.y = (cnv.h / 2) - scene->mouse.y;
	catch_ray.d = throught_vp(cnv, vp);
	catch_ray.d = mat_apply(scene->cam.t_m, catch_ray.d);
	catch_ray.o = scene->cam.t_m.p;
	scene->selected = closest_intersect(&catch_ray, 0, 0.001f, T_MAX, scene->objects);
	if (scene->selected && scene->selected != obj)
	{
		if (obj)
			obj->color = last_color;
		last_color = scene->selected->color;
		scene->selected->color = (t_argb) {255, 255, 255, 255};
	}
	else if (scene->selected && scene->selected == obj)
	{
		scene->selected->color = last_color;
		scene->selected = NULL;
		obj = NULL;
	}

}

int	mouse_press(int keycode, int x, int y, t_data *scene)
{
	(void)keycode;
	scene->mouse.x = x;
	scene->mouse.y = y;
	scene->mouse_state = 1;
	select_object(scene);
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
