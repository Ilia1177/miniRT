#ifndef MINIRT_H
# define MINIRT_H
# include <mlx.h>
# include <libft.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
# include <float.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define HEIGHT 800
# define WIDTH 800
# define RECURSION_LIMIT 8

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

typedef struct	s_camera
{
	t_vec3 pos;
    t_vec3 dir;   // Forward direction
    t_vec3 right; // Right direction
	t_vec3 up;    // Up direction
    float yaw;   // Horizontal rotation (left/right)
    float pitch; // Vertical rotation (up/down)
}	t_camera;

typedef struct	s_viewport
{
	t_vec3		pos;
	t_vec3		loc;
	int			h;
	int			w;
}	t_viewport;

typedef struct	s_canvas
{
	t_vec2		loc;
	int			h;
	int			w;
}	t_canvas;

/* typedef struct s_object */
/* { */
/* 	type; */

/* } */
typedef	struct	s_sphere
{
	float	closest_t;
	float	intersection[2];
	int		color;
	t_vec3	pos;
	float	radius;
	int		specular;
	float		reflective;
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

typedef enum e_ltype
{
	POINT,
	AMBIENT,
	DIRECTIONAL,
}	t_ltype;

typedef struct	s_light
{
	t_ltype			type;
	float			intensity;
	t_vec3			pos;
	t_vec3			dir;
	struct s_light *next;
}	t_light;

typedef enum	e_otype
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_otype;

typedef struct	s_object
{
	float	intersection[2];
	t_otype			type;
	t_vec3			pos;	
	int				specular;
	float			radius;
	float			len;
	float			reflective;
	float			discriminant;
	unsigned int	color;

	t_sphere		sphere;
	//t_cylinder		cylinder;
	//t_plane			plane;
	struct s_object	*next;
}	t_object;

typedef struct	s_data
{
	char		*map_name;
	float		intersec_p[2];
	void		*mlx;
	void		*win;
	t_img		img;
	t_canvas	cnv;
	t_camera	cam;
	t_vec3		rotation_matrix[3];
	t_viewport	viewport;
	t_object	*objects;
	t_light		*light;
	t_vec2		mouse;
	int			mouse_state;
	char		key_state[99999];
}				t_data;

//init.c
int				rt_init(t_data *scene, int *status);
int				rt_shut_down(t_data *scene);

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
unsigned int			throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene);
t_vec3		get_viewport_loc(t_canvas cnv, t_viewport vp);
void		display_color(t_data *scene);
t_vec2		cnv_to_screen(t_canvas cnv);
int			intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *object);
t_object	*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_data *scene);

//light.c
float	compute_lighting(t_vec3 point, t_vec3 norm, t_vec3 v, int specular, t_data *scene);
unsigned int mult_colors(unsigned int color, float factor);
t_vec3 reflect_ray(t_vec3 ray, t_vec3 norm);
unsigned int add_colors(unsigned int c1, unsigned int c2);

t_vec3	cross_vec3(t_vec3 a, t_vec3 b);
float	dot_product(t_vec3 a, t_vec3 b);
float	mag_vec3(t_vec3 a);
double	dist(t_vec2 a, t_vec2 b);
t_vec3	sub_vec3(t_vec3 a, t_vec3 b);
t_vec3	add_vec3(t_vec3 a, t_vec3 b);
t_vec3	normalize_vec3(t_vec3 vec);
t_vec3	div_vec3(t_vec3 vec, float d);
t_vec3	mult_vec3(t_vec3 vec, float a);

//camera.c
void update_camera_vectors(t_camera *cam);
t_vec3 apply_camera_rotation(t_camera cam, t_vec3 v);
void mouse_move(t_camera *cam, float delta_x, float delta_y);

// debug
void	print_vec3(t_vec3 v, char *msg);

//clean.c
void	free_sphere(t_sphere *sphere);
void	free_light(t_light *light);

//scene
int	build_scene(t_data *scene);

#endif
