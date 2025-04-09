NAME = miniRT
BONUS_NAME = miniRT_bonus

UNAME = $(shell uname)
SRCS_DIR = srcs
BONUS_SRCS_DIR = srcs_bonus
OBJS_DIR = objs
BONUS_OBJS_DIR = objs_bonus
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
CLONE = mlx

ifeq ($(shell uname), Linux)
	CFLAGS = -g -Wall -Wextra -Werror -g #-fsanitize=address
	INCLUDES = -I/usr/include -I./mlx -I./libft/include -I./include
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm 
else
	CFLAGS = -g #-Wall -Wextra -Werror -g #-fsanitize=address
	INCLUDES =  -I./mlx -I./libft/include -I./include# -I/opt/X11/include
	MLX_FLAGS = -L./libft/bin -L./mlx -L/usr/X11/lib -lft -lmlx -lXext -lX11 -lm -framework OpenGL -framework AppKit
endif

LIBFT = libft/bin/libft.a

SRCS = 	miniRT.c\
		build_scene.c\
		camera.c\
		camera_move.c\
		canvas.c\
		clean.c\
		color.c\
		cylinder_utils.c\
		debug.c\
		img.c\
		init.c\
		input.c\
		inter_cyl_utils.c\
		intersection.c\
		light.c\
		lst_cylinder.c\
		lst_light.c\
		lst_plane.c\
		lst_sphere.c\
		norm_utils.c\
		normal.c\
		parsing_utils.c\
		ray.c\
		rotation_object.c\
		text_checkerboard.c\
		text_img.c\
		vector.c\
		lst_hyperboloid.c\
		dl_img.c\
		matrix.c\

BONUS_SRCS = 	miniRT_bonus.c\
				build_scene_bonus.c\
				camera_bonus.c\
				camera_move_bonus.c\
				canvas_bonus.c\
				clean_bonus.c\
				color_bonus.c\
				cylinder_utils_bonus.c\
				debug_bonus.c\
				img_bonus.c\
				init_bonus.c\
				input_bonus.c\
				inter_cyl_utils_bonus.c\
				intersection_bonus.c\
				light_bonus.c\
				lst_cylinder_bonus.c\
				lst_light_bonus.c\
				lst_plane_bonus.c\
				lst_sphere_bonus.c\
				norm_utils_bonus.c\
				normal_bonus.c\
				parsing_utils_bonus.c\
				ray_bonus.c\
				rotation_object_bonus.c\
				text_checkerboard_bonus.c\
				text_img_bonus.c\
				vector_bonus.c\
				lst_hyperboloid_bonus.c\
				dl_img_bonus.c\
				matrix_bonus.c\

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
BONUS_SRCS := $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_SRCS_DIR)/%.c=$(BONUS_OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

CC = cc -MMD 

all : $(LIBFT) $(MLX_LIB) $(NAME)

bonus : $(LIBFT) $(MLX_LIB) $(BONUS_NAME)

$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	mkdir -p $(BONUS_OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(BONUS_NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB): $(CLONE) 
	make -C $(MLX_DIR) 

$(CLONE) : 
	git clone https://github.com/42Paris/minilibx-linux.git $(CLONE)

$(LIBFT) : 
	make -C libft

clean	:
	-make clean -C libft
	-make clean -C $(MLX_DIR)
	-rm -fr $(OBJS_DIR)

fclean	: clean
	-make fclean -C libft
	-rm $(NAME)
	-rm $(BONUS_NAME)

re		: fclean all

.PHONY : all clean fclean re bonus

-include $(DEPS)
