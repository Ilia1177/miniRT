# include <mlx.h>
# include <libft.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/X.h>
#include <math.h>
#include <stdio.h>

#define HEIGHT 800
#define WIDTH 800
#define RAY_NUMBER 100

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_viewport
{
	t_vec3		pos;
	t_vec3		loc;
	int			h;
	int			w;
}	t_viewport;

typedef struct	s_canvas
{
	//t_vec2		loc;
	int			h;
	int			w;
}	t_canvas;

typedef	struct	s_sphere
{
	int		color;
	t_vec3	pos;
	float	radius;
	struct s_sphere	*next;
}			t_sphere;

typedef struct	s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
}			t_img;

typedef enum e_type
{
	POINT,
	AMBIENT,
	DIRECTIONAL,
}	t_type;

typedef struct	s_light
{
	t_type	type;
	float	intensity;
	t_vec3	pos;
	t_vec3	dir;
}	t_light;

typedef struct	s_data
{

	void		*mlx;
	void		*win;
	t_img		img;
	t_canvas	cnv;
	t_vec3		cam;
	t_viewport	viewport;
	t_light		*light;
	t_sphere	*sphere;
	t_vec2		mouse;
	int			mouse_state;
	int			key_state[99999];
}				t_data;

//init.c
int				rt_init(t_data *scene);
int			rt_shut_down(t_data *scene);

//img.c
void			rt_put_pixel(t_img *img, t_vec2 pix, int color);
unsigned int	rt_get_pixel(t_img img, int x, int y);

//input.c
int		mouse_press(int keycode, int x, int y, t_data *scene);
int		mouse_release(int keycode, int x, int y, t_data *scene);
int		key_release(int keycode, t_data *scene);
int		key_press(int keycode, t_data *scene);
int		handle_input(t_data *scene);
int		mouse_pos(int x, int y, t_data *scene);

//ray
int	throw_ray(t_vec3 cam, t_vec3 dir, int t_min, int t_max, t_data *scene);
t_vec3 get_viewport_loc(t_canvas cnv, t_viewport vp);
void	display_color(t_data *scene);
t_vec2 cnv_to_screen(t_canvas cnv);
float *IntersectRaySphere(t_vec3 cam, t_vec3 dir, t_sphere sphere);


float	dot_product(t_vec3 a, t_vec3 b);
float	mag_vec3(t_vec3 a);
double	dist(t_vec2 a, t_vec2 b);
t_vec3	sub_vec3(t_vec3 a, t_vec3 b);
t_vec3	add_vec3(t_vec3 a, t_vec3 b);
