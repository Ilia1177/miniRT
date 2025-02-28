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

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		end;
}				t_ray;

typedef	struct	s_rect
{
	t_vec2		pos;
	t_vec2		size;
	float		angle;
}				t_rect;

typedef	struct	s_sphere
{
	t_vec3	pos;
	float	radius;
	t_ray	*light;
}			t_sphere;

typedef	struct	s_circle
{
	t_vec2	pos; //to be renamed pos
	float	radius;
	t_ray	*light;
}			t_circle;

typedef struct	s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
}			t_img;

typedef struct	s_viewport
{
	t_vec3	pos;
	t_vec2	size;
}				t_viewport;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_viewport	viewport;
	t_vec3		camera;
	t_vec3		light;
	t_sphere	sphere;
	t_vec2		mouse;
	int			mouse_state;
	int			key_state[99999];
}				t_data;

//init.c
int				rt_init(t_data *scene);
int			rt_shut_down(t_data *scene);

//img.c
void			rt_put_pixel(t_img *img, int x, int y, int color);
unsigned int	rt_get_pixel(t_img img, int x, int y);

//input.c
int		mouse_press(int keycode, int x, int y, t_data *scene);
int		mouse_release(int keycode, int x, int y, t_data *scene);
int		key_release(int keycode, t_data *scene);
int		key_press(int keycode, t_data *scene);
int		handle_input(t_data *scene);
int		mouse_pos(int x, int y, t_data *scene);

//geo.c
int	rt_ray(t_ray ray, t_circle object, t_img *img);
int				rt_circle(t_circle circle, t_img *img);
int				rt_rect(t_rect rect, t_img *img);
