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
# define CBOARD_W 24
# define CBOARD_H 24
# define CBOARD_SCALE 0.22f
# define CBOARD_COLOR (t_argb){0, 255, 255, 255}
# define ABS(x) ((x<0)*-x)+((x>0)*x)

//add w for the structure to be aligned on 16 bytes properly;
typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
	float		w;
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

//16 bytes aligned: OK
typedef struct	s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
}	t_argb;

//	typedef struct s_ftab
//	o{
//	}

//24 bytes not aligned
typedef struct s_quad
{
	float	t[2];
	float	delta;
	float	a;
	float	b;
	float	c;
}	t_quad;

typedef struct  s_board
{
	t_argb color[CBOARD_H][CBOARD_W];
}   t_board;

typedef struct s_uv
{
    float u;
    float v;
} t_uv;

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
//	t_vec3		pos;
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

typedef enum e_type
{
	POINT,
	AMBIENT,
	DIRECTIONAL,
	SPHERE,
	PLANE,
	CYLINDER,
	HYPERBOL,
}	t_type;

typedef struct	s_light
{
	struct s_light	*next;
	t_argb			intensity;
	t_vec3			pos;
	t_vec3			dir;
	t_type			type;
}	t_light;

//64 bytes aligned: OK
typedef struct	s_ray
{
	t_vec3	v;
	t_vec3	d;
	t_vec3	o;
	t_vec3	n;
}	t_ray;

typedef struct	s_object
{
	struct s_object	*next;
	t_argb			reflect;
	t_argb			color;
	t_vec3			pos;
	t_vec3			axis;
	t_vec3			scale;
	t_vec3			up;
	t_vec3			dir;
	t_vec3			right;
	float			yaw;
	float			pitch;
	float			t;
	float			radius;
	float			height;
	int				spec;
	int				pattern;
	t_type			type;
}	t_object;

typedef struct	s_data
{
	char		key_state[99999];
	void		*mlx;
	void		*win;
	char		*map_name;
	char		rend;
	char		res;
//	float		intersec_p[2];
	t_img		img;
	t_canvas	cnv;
	t_camera	cam;
//	t_vec3		rotation_matrix[3];
	t_viewport	viewport;
	t_object	*selected;
	t_object	*objects;
	t_light		*lights;
	t_vec2		mouse;
	int			mouse_state;
}				t_data;

//init.c
int				rt_init(t_data *scene, int *status);
int				rt_shut_down(t_data *scene);

//img.c
void			rt_put_pixel(t_img *img, int x, int y, int color);
unsigned int	rt_get_pixel(t_img img, int x, int y);
int				encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int				encode_img_argb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
t_rgb			extract_rgb(int color);
t_argb			extract_argb(int color);

//norm_utils.c
void			norm_rgb(t_rgb *c);
void			norm_float(float *f, float min, float max);
void			norm_int(int *num, int min, int max);

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
t_argb			throw_ray(t_ray *ray, float t_min, float t_max, int rec, t_data *scene);
t_object		*closest_intersect(t_ray *ray, int shadow, float t_min, float t_max, t_object *obj);
t_quad			solve_quadratic(t_vec3 oc, t_vec3 dir, float radius);
//intersection.c
int				intersect_object(t_ray *ray, t_object *obj, float *t);
int				intersect_sphere(t_ray *ray, t_object *object, float *t);
int 			intersect_cylinder(t_ray *ray, t_object *cylinder, float *t);
int				intersect_plane(t_ray *ray, t_object *plane, float *t);
int				intersect_hyperboloid(t_ray *ray, t_object *hyperb, float *t);


//normal.c
void	cylinder_normal(t_ray *ray, t_object *cylinder);
void	plane_normal(t_ray *ray, t_object *plane);
void	sphere_normal(t_ray *ray, t_object *sphere);
void hyperboloid_normal(t_ray *ray, t_object *object);

//color.c
void			limit_color(t_argb *color);
t_argb			ease_color(t_argb reflective, uint8_t factor);
t_argb			mult_colors(t_argb color1, t_argb intensity);
t_argb 			add_colors(t_argb c1, t_argb c2);
unsigned int 	encode_argb(t_argb color);
void			add_bright_argb(t_argb *color, float bright);

//light.c
t_argb			compute_lighting(t_ray *ray, t_object *obj, t_data *scene);
void			reflect_ray(t_ray *ray);
t_argb			specular_reflect(t_vec3 v, t_vec3 r, float r_dot_v, int spec, t_argb intensity);
t_argb			diffuse_reflect(t_ray *ray, t_argb lumen, float n_dot_l);
t_argb			reflections(t_ray *ray, t_argb intensity, int spec);

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
void	print_error_msg(int status);
void	print_light(t_light light);
void	print_cam(t_camera camera);

//clean.c
void	free_light(t_light *light);
void	free_data(t_data *scene);

//build_scene.c
int	build_scene(t_data *scene);
void	init_obj(t_object *obj, t_type type);

//Parsing_utils.c
int	str_to_vec3(char **line, t_vec3 *v);
int	str_to_argb(char **line, t_argb *c, int get_alpha);
int	skip_space(char *str);
int	str_to_float(char **line, float *radius);
int	str_to_vecdir(char **line, t_vec3 *v);
int	get_options(char **line, t_object *obj);

int	make_object(t_object data, t_object **objects);
//init.c
int	scene_init(t_data *scene);

//lst_sphere.c
int	create_sphere(char **line, t_data *scene);

//lst_cylinder.c
int	create_cylinder(char **line, t_data *scene);

//lst_plane.c
int	create_plane(char **line, t_data *scene);

//lst_light.c
int	create_light(char **line, t_data *scene, t_type type);
int	clean_lights(t_data *scene);

int	make_hyperboloid(t_object data, t_object **objects);

//rotation_object.c
void	rotate(t_object *obj);
void	rotate_on_z(t_object *obj, float theta);
void	rotate_on_y(t_object *obj, float theta);
	void	rotate_on_x(t_object *obj, float theta);

//text_checkerboard.c
t_argb	pattern_color(t_ray *ray, t_object *obj);

//cylinder_utils.c
t_vec3  cy_center_to_base(t_object cy);
t_vec3 cy_base_to_center(t_vec3 pos, t_vec3 dir, float height);

//dl_img.c
void save_as_ppm(t_img *img, char *filename);

#endif
