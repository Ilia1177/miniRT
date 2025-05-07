#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# include <mlx.h>
# include <libft.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
//# include <float.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>
//# include <stdatomic.h>
//# include <semaphore.h>
# include <sys/time.h>
//#include <atomic.h>
# define MAX_SCALE 1000
# define T_MAX 1600
# define HEIGHT 800
# define WIDTH 800 
# define R_LIMIT 3 // limit to recursion (reflect ray)
# define SPECULAR 500
# define MOUSE_SENSITIVITY 0.5f
# define FLT_MAX     3.40282347E+38F
# define CBOARD_W 40
# define CBOARD_H 40
# define CBOARD_SCALE 1.0f
//# define CBOARD_COLOR (t_argb){0, 255, 255, 255}
//# define ABS(x) ((x<0)*-x)+((x>0)*x) //forbiden
//# define EPSILON 1.0e-6
# define EPSILON 0.001f
# define MSG_BAD_FILE	"Error\nNeed one file *.rt\n"
# define MSG_BAD_POS	"Bad position arguments.\n"
# define MSG_BAD_RGB	"Bad rgb arguments.\n"
# define MSG_BAD_FLT	"Bad float arguments.\n"
# define MSG_BAD_TYPE	"Bad type arguments, only A,C,L,sp,pl,cy allowed\n"
# define MSG_BAD_LGHT	"Error\nWrong number of light:need one ambient and one spot\n"
# define MSG_BAD_ELEM	"Error\nWrong number of element:at least one sphere, one cylinder, one plane\n"
# define MSG_BAD_OPT 	"Wrong options arguments\n"
# define MSG_BAD_CAM "Error\nNeed one camera\n"
# define MSG_BAD_MALL "Error\nMalloc error\n"
# define MSG_BAD_MLX "Error\nMlx init\n"
# define MSG_BAD_WIN "Error\nMlx window\n"
# define MSG_BAD_IMG "Error\nMlx image\n"
# define MSG_BAD_ADD "Error\nMlx image address\n"

//add w for the structure to be aligned on 16 bytes properly;
typedef struct s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct s_mat4
{
	t_vec4	i;
	t_vec4	j;
	t_vec4	k;
	t_vec4	p;
}	t_mat4;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
}	t_argb;

typedef struct s_quad
{
	float	t[2];
	float	delta;
	float	a;
	float	b;
	float	c;
}	t_quad;

typedef struct s_board
{
	t_argb	color[CBOARD_H][CBOARD_W];
}	t_board;

typedef struct s_uv
{
	float	u;
	float	v;
}	t_uv;

typedef struct s_camera
{
	t_mat4	t_m;
	t_mat4	i_m;
	float	yaw;
	float	pitch;
	int		fov;
}	t_camera;

typedef struct s_viewport
{
	t_vec4		loc;
	int			h;
	int			w;
}	t_viewport;

typedef struct s_canvas
{
	t_vec2		loc;
	int			h;
	int			w;
}	t_canvas;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	int		w;
	int		h;	
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
	TRIANGLE,
}	t_type;

typedef struct s_light
{
	struct s_light	*next;
	t_argb			intensity;
	t_vec4			pos;
	t_vec4			dir;
	t_type			type;
}	t_light;

//64 bytes aligned: OK
typedef struct s_ray
{
	t_vec4	v;
	t_vec4	d;
	t_vec4	o;
	t_vec4	n;
}	t_ray;

// t_mat = matrix world space
// i_mat = invert matrix
typedef struct s_object
{
	struct s_object	*next;
	t_argb			reflect;
	t_argb			color;
	char			mat[4][4];
	t_vec4			vertice[3];
	t_mat4			t_m;
	float			t;
//	t_mat4			i_m;
	t_vec4			scale;
	float			radius;
	float			height;
	int				spec;
	int				pattern;
	char			*path;
	t_img			*img;
	int				opt;
	t_type			type;
}	t_object;

typedef struct s_painter
{
	float			lim[3];
//	pthread_mutex_t	brush;
//	int			ready;
	float			t;
	t_ray			ray;
	pthread_t		itself;
	int				id;
	int				done;
	struct s_data	*sceneref;
}	t_painter;

typedef struct s_data
{
	pthread_mutex_t	print;
	pthread_mutex_t	announce;
	pthread_cond_t	painter_rest;
	pthread_cond_t	master_rest;
	struct timeval	start;
	int				processing;
	int				at_rest;
	int				status;
	void			*mlx;
	void			*win;
	char			*map_name;
	char			rend;
	char			res;
	t_painter		painter;
//	pthread_t	listener;
//	float		intersec_p[2];
	t_img			img;
	//t_img		earth;
	t_canvas		cnv;
	t_camera		cam;
//	t_vec4		rotation_matrix[3];
	t_viewport		viewport;
	t_object		*selected;
	t_object		*objects;
	t_light			*lights;
//	t_vec2		mouse;
	int				mouse_state;
	char			key_state[99999];
}				t_data;

//thread
int			th_master_start(t_data *scene);
int			th_painter_start(t_data *scene);
int			th_painter_wait(t_data *scene);
t_painter	th_painter_init(t_data *scene, int i);
void		th_painer_quit(t_data *scene);
void		*th_painter_draw(void *painter);
void		th_painter_kill(t_data *scene);

//camera move
void		rotate_y(t_camera *cam, float theta);
void		rotate_x(t_camera *cam, float theta);
//matrix.c

void		mat_scale(t_mat4 *m, float sx, float sy, float sz);
void		mat_transpose_inverse(t_mat4 mat);
void		mat_rotate(t_mat4 *m, float dx, float dy, float dz);
void		mat_translate(t_mat4 *m, float dx, float dy, float dz);
t_vec4		mat_apply(t_mat4 mat, t_vec4 v);
t_mat4		mat_generate(t_object *obj);
t_mat4		mat_compose(t_mat4 m2, t_mat4 m1);
t_mat4		mat_transpose(t_mat4 m);
t_mat4		mat_init_id(void);
t_mat4		mat_orthogonal(t_vec4 dir);
t_mat4		mat_inverse(t_mat4 matrix);

//img.c
void		rt_rect(const t_img *img, t_vec2 pos, t_vec2 size, int color);
void		rt_put_pixel(const t_img *img, int x, int y, int color);
uint8_t		rt_get_pixel(t_img img, int x, int y);
t_argb		extract_argb(int color);

//norm_utils.c
void		norm_rgb(t_rgb *c);
void		norm_float(float *f, float min, float max);
void		norm_int(int *num, int min, int max);

//input.c
int			mouse_press(int keycode, int x, int y, t_data *scene);
int			mouse_release(int keycode, int x, int y, t_data *scene);
int			key_release(int keycode, t_data *scene);
int			key_press(int keycode, t_data *scene);
int			handle_input(t_data *scene);
int			mouse_pos(int x, int y, t_data *scene);

//canvas.c
t_vec4		throught_vp(t_vec2 cnv, t_viewport vp);
void		display_color(t_painter *painter);
t_vec2		cnv_to_screen(t_vec2 cnv);

//ray

//inter_utils.c
//int	intersect_disk(t_ray *ray, t_vec4 center, t_object *cyl, float *t);
//int	intersect_cylinder_lateral(t_ray *ray, t_object *cy, float *t);
//int check_height_cylinder(t_ray *ray, t_object *cy, float *t, t_quad quad);
//void get_min_t(float *t_min, float t_tmp, int *hit);
//int	min_pos(float *t, float t1, float t2);

//ray && intersection.c
t_argb		throw_ray(t_painter *painter);
t_object	*closest_intersect(t_painter *painter, int shadow, t_object *obj);
int			solve_quadratic(t_quad *quad);
int			intersect_triangle(t_ray *ray, t_object *tr, float *t);
int			intersect_object(t_ray *ray, t_object *obj, float *t);
int			intersect_sphere(t_ray *ray, t_object *object, float *t);
int			intersect_cylinder(t_ray *ray, t_object *cylinder, float *t);
int			intersect_plane(t_ray *ray, t_object *plane, float *t);
int			intersect_hyperboloid(t_ray *ray, t_object *hyperb, float *t);

//normal.c
void		triangle_normal(t_ray *ray, t_object *tr);
void		cylinder_normal(t_ray *ray, t_object *cy);
void		plane_normal(t_ray *ray, t_object *pl);
void		sphere_normal(t_ray *ray, t_object *sp);
void		hyperboloid_normal(t_ray *ray, t_object *hy);

//color.c
t_argb		invert_color(t_argb color);
void		limit_color(t_argb *color);
t_argb		ease_color(t_argb reflective, uint8_t factor);
t_argb		mult_colors(t_argb color1, t_argb intensity);
t_argb		add_colors(t_argb c1, t_argb c2);
uint32_t		encode_argb(t_argb color);
t_argb		apply_brightness(t_argb color);

//light.c
t_argb		compute_lighting(t_painter *painter, t_object *obj);
void		reflect_ray(t_ray *ray);
t_argb		specular_reflect(t_vec4 v, t_vec4 r, float r_dot_v, int spec, t_argb intensity);
t_argb		diffuse_reflect(t_ray *ray, t_argb lumen, float n_dot_l);
t_argb		reflections(t_ray *ray, t_argb intensity, int spec);

//vector_math.c
t_vec4		random_vec4(float magnitude);
t_vec4		cross_vec4(t_vec4 a, t_vec4 b);
float		dot_vec4(t_vec4 a, t_vec4 b);
float		dot_vec3(t_vec4 a, t_vec4 b);
float		mag_vec4(t_vec4 a);
double		dist(t_vec2 a, t_vec2 b);
t_vec4		sub_vec4(t_vec4 a, t_vec4 b);
t_vec4		add_vec4(t_vec4 a, t_vec4 b);
t_vec4		normalize_vec4(t_vec4 vec);
t_vec4		div_vec4(t_vec4 vec, float d);
t_vec4		mult_vec4(t_vec4 vec, float a);
float		dist_vec4(t_vec4 a, t_vec4 b);

//camera_vectors.c
void		update_camera_rotation(t_camera *cam);
//t_vec4	apply_camera_rotation(t_camera cam, t_vec4 v);
//void	mouse_move(t_camera *cam, float delta_x, float delta_y);
float		calc_vp_width(float fov_degrees, float focal_length);

//camera_move.c
void		translate_camera(t_camera *camera, float dx, float dy, float dz);
void		rotate_camera(t_camera *camera, float dx, float dy, float dz);

// debug

long long	time_from(struct timeval *last);
void		th_annouce(char *msg, t_painter *painter);
void		print_painter(t_painter *painter);
void		print_mat4(t_mat4 matrix); // for loop
void		print_obj(t_object obj);
void		print_light(t_light light);
void		print_cam(t_camera camera);

//print
void		print_error_msg(int status, t_data *scene);
void		print_vec4(t_vec4 v, char *msg);
void		print_argb(t_argb color, char *msg);
void		print_input(void);

//clean.c
void		free_light(t_light *light);
void		free_data(t_data *scene);
int			rt_shut_down(t_data *scene);

//build_scene.c
int			build_scene(t_data *scene);
void		init_obj(t_object *obj, t_type type);

//build_scene_utils.c
int			ambient_exist(t_data *scene);
int			go_to_endl(char *str);
void		print_all(t_data *scene);

//Parsing_utils.c
int			str_to_vec4(char **line, t_vec4 *v, float w);
int			str_to_argb(char **line, t_argb *c, int get_alpha);
int			skip_space(char *str);
int			str_to_float(char **line, float *radius);
int			str_to_vecdir(char **line, t_vec4 *v);
int			get_options(char **line, t_object *obj);

//Parsing_utils_2
int			check_nb_obj(t_data *scene);
int			check_nb_light(t_data *scene);

int			make_object(t_object data, t_object **objects);
//init.c

//int		rt_scene_tozero(t_data *scene);
//void	mlx_tozero(t_data *scene);
int			rt_init(t_data *scene, char **av, int ac);

//lst_sphere.c
int			create_sphere(char **line, t_data *scene);

//lst_cylinder.c
int			create_cylinder(char **line, t_data *scene);

//lst_plane.c
int			create_plane(char **line, t_data *scene);

//lst_light.c
int			create_light(char **line, t_data *scene, t_type type);
int			clean_lights(t_data *scene);

int			create_triangle(char **line, t_data *scene);
int			create_hyperboloid(char **line, t_data *scene);

//rotation_object.c
void		rotate(t_object *obj);
void		rotate_on_z(t_object *obj, float theta);
void		rotate_on_y(t_object *obj, float theta);
void		rotate_on_x(t_object *obj, float theta);

//text_checkerboard.c
t_argb		pattern_color(t_ray *ray, t_object *obj, t_data *scene);

//text_img
t_argb		text_img_at(float u, float v, t_img *img);
t_img		*text_img(t_data *scene, char *path);

//cylinder_utils.c
t_vec4		cy_center_to_base(t_object cy);
t_vec4		cy_base_to_center(t_vec4 pos, t_vec4 dir, float height);

//dl_img.c
void		save_as_ppm(t_img *img, char *filename);

#endif
