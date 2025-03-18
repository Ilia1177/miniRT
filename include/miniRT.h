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

# define T_MAX 1000
# define HEIGHT 800
# define WIDTH 800
# define R_LIMIT 3 // limit to recursion (reflect ray)
# define SPECULAR 500
# define MOUSE_SENSITIVITY 0.5f
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

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct	s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
}	t_argb;

typedef struct s_quad
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t[2];
}	t_quad;

typedef struct	s_camera
{
	t_vec3 pos;
    t_vec3 dir;   	// Forward direction
    t_vec3 right; 	// Right direction
	t_vec3 up;    	// Up direction
    float yaw;   	// Horizontal rotation (left/right)
    float pitch; 	// Vertical rotation (up/down)
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
	t_argb			intensity;
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
	float			t[2];
	float			closest_t;
	t_otype			type;
	t_vec3			pos;
	t_vec3			orientation;
	int				spec;
	float			radius;
	float			height;
	t_argb			reflect;
	t_argb			color;
	struct s_object	*next;
}	t_object;

typedef struct	s_data
{
	char		res;
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
	t_light		*lights;
	t_vec2		mouse;
	int			mouse_state;
	char		key_state[99999];
}				t_data;

//init.c
int				rt_init(t_data *scene, int *status);
int				rt_shut_down(t_data *scene);

//img.c
void			rt_put_pixel(t_img *img, int x, int y, int color);
unsigned int	rt_get_pixel(t_img img, int x, int y);
int				encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
t_rgb			extract_rgb(int color);
void			norm_rgb(t_rgb *c);

//input.c
int		mouse_press(int keycode, int x, int y, t_data *scene);
int		mouse_release(int keycode, int x, int y, t_data *scene);
int		key_release(int keycode, t_data *scene);
int		key_press(int keycode, t_data *scene);
int		handle_input(t_data *scene);
int		mouse_pos(int x, int y, t_data *scene);
//canvas.c
t_vec3		get_viewport_loc(t_canvas cnv, t_viewport vp);
void		display_color(t_data *scene);
t_vec2		cnv_to_screen(t_canvas cnv);

//ray
t_argb			throw_ray(t_vec3 origin, t_vec3 dir, float t_min, float t_max, int rec, t_data *scene);
t_object		*closest_intersect(t_vec3 origin, t_vec3 dir, float t_min, float t_max, t_object *obj);
t_quad			solve_quadratic(t_vec3 oc, t_vec3 dir, float radius);
//intersection.c
int				intersect_object(t_vec3 origin, t_vec3 dir, t_object *obj, float *t);
int				intersect_sphere(t_vec3 origin, t_vec3 dir, t_object *object, float *t);
int 			intersect_cylinder(t_vec3 origin, t_vec3 dir, t_object *cylinder, float *t);
int				intersect_plane(t_vec3 origin, t_vec3 dir, t_object *plane, float *t);


//normal.c
t_vec3	cylinder_normal(t_vec3 pt, t_object *cylinder);
t_vec3	plane_normal(t_vec3 dir, t_vec3 norm);
t_vec3	sphere_normal(t_vec3 pt, t_vec3 o, t_vec3 dir, t_object *sphere);

//color.c
void			limit_color(t_argb *color);
t_argb			ease_color(t_argb reflective, uint8_t factor);
t_argb			mult_colors(t_argb color1, t_argb intensity);
t_argb 			add_colors(t_argb c1, t_argb c2);
unsigned int 	encode_argb(t_argb color);

//light.c
t_argb			compute_lighting(t_vec3 pt, t_vec3 n, t_vec3 v, int spec, t_data *scene);
t_vec3			reflect_ray(t_vec3 dir, t_vec3 norm);
t_argb			specular_reflect(t_vec3 v, t_vec3 r, float r_dot_v, int spec, t_argb intensity);
t_argb			diffuse_reflect(t_argb intensity, t_vec3 norm, t_vec3 l_dir, float n_dot_l);
t_argb			reflections(t_vec3 d, t_vec3 v, t_vec3 n, t_argb intensity, int spec);

//vector_math.c
t_vec3	cross_vec3(t_vec3 a, t_vec3 b);
float	dot_vec3(t_vec3 a, t_vec3 b);
float	mag_vec3(t_vec3 a);
double	dist(t_vec2 a, t_vec2 b);
t_vec3	sub_vec3(t_vec3 a, t_vec3 b);
t_vec3	add_vec3(t_vec3 a, t_vec3 b);
t_vec3	normalize_vec3(t_vec3 vec);
t_vec3	div_vec3(t_vec3 vec, float d);
t_vec3	mult_vec3(t_vec3 vec, float a);
float	dist_vec3(t_vec3 a, t_vec3 b);

//camera_vectors.c
void	update_camera_vectors(t_camera *cam);
t_vec3	apply_camera_rotation(t_camera cam, t_vec3 v);
void	mouse_move(t_camera *cam, float delta_x, float delta_y);
float	calc_vp_width(float fov_degrees, float focal_length);

//camera_move.c
void move_camera_forward(t_camera *cam, float speed);
void move_camera_backward(t_camera *cam, float speed);
void move_camera_right(t_camera *cam, float speed);
void move_camera_left(t_camera *cam, float speed);

// debug
void	print_argb(t_argb color, char *msg);
void	print_vec3(t_vec3 v, char *msg);
void	print_obj(t_object obj);

//clean.c
void	free_light(t_light *light);

//scene
int	build_scene(t_data *scene);

//Parsing_utils.c
int	str_to_vec3(char **line, t_vec3 *v);
int	str_to_rgb(char **line, t_rgb *c);
int	skip_space(char *str);
int	str_to_radius(char **line, float *radius);

//init.c
int	scene_init(t_data *scene);

#endif
