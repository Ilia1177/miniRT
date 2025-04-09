NAME = miniRT
<<<<<<< HEAD
BONUS_NAME = miniRT_bonus

UNAME = $(shell uname)
SRCS_DIR = srcs
BONUS_SRCS_DIR = srcs_bonus
OBJS_DIR = objs
BONUS_OBJS_DIR = objs_bonus
=======
NAME_BONUS = Hazardous_miniRT

UNAME = $(shell uname)
SRCS_DIR = srcs
SRCS_BONUS_DIR = srcs_bonus
OBJS_DIR = objs
OBJS_BONUS_DIR = objs_bonus
>>>>>>> jm-test
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

SRCS = 	miniRT\
		build_scene\
		camera\
		camera_move\
		canvas\
		clean\
		color\
		cylinder_utils\
		debug\
		img\
		init\
		input\
		inter_cyl_utils\
		intersection\
		light\
		lst_cylinder\
		lst_light\
		lst_plane\
		lst_sphere\
		norm_utils\
		normal\
		parsing_utils\
		ray\
		rotation_object\
		vector\
		lst_hyperboloid\
		dl_img\
		matrix\

<<<<<<< HEAD
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
=======
SRCS_BONUS = 	miniRT\
		build_scene\
		camera\
		camera_move\
		canvas\
		clean\
		color\
		cylinder_utils\
		debug\
		img\
		init\
		input\
		inter_cyl_utils\
		intersection\
		light\
		lst_cylinder\
		lst_light\
		lst_plane\
		lst_sphere\
		norm_utils\
		normal\
		parsing_utils\
		ray\
		rotation_object\
		text_checkerboard\
		text_img\
		vector\
		lst_hyperboloid\
		dl_img\
		matrix\

SRCS := $(addsuffix .c, $(SRCS))
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

SRCS_BONUS := $(addsuffix _bonus.c, $(SRCS_BONUS))
SRCS_BONUS := $(addprefix $(SRCS_BONUS_DIR)/, $(SRCS_BONUS))

>>>>>>> jm-test
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_SRCS_DIR)/%.c=$(BONUS_OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

OBJS_BONUS = $(SRCS_BONUS:$(SRCS_BONUS_DIR)/%.c=$(OBJS_BONUS_DIR)/%.o)
DEPS_BONUS = $(OBJS_BONUS:%.o=%.d)

CC = cc -MMD 

all : $(LIBFT) $(MLX_LIB) $(NAME)

bonus : $(LIBFT) $(MLX_LIB) $(BONUS_NAME)

$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	mkdir -p $(BONUS_OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

bonus :  $(LIBFT) $(MLX_LIB) $(NAME_BONUS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

<<<<<<< HEAD
$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(BONUS_NAME)
=======
$(OBJS_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
	mkdir -p $(OBJS_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
>>>>>>> jm-test

$(NAME): $(OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME_BONUS) -L./libft/bin -lft

$(MLX_LIB): $(CLONE) 
	make -C $(MLX_DIR) 

$(CLONE) : 
	git clone https://github.com/42Paris/minilibx-linux.git $(CLONE)

$(LIBFT) : 
	make -C libft

clean	:
	@echo "Cleaning object files..."
	-make clean -C libft
	-make clean -C $(MLX_DIR)
<<<<<<< HEAD
	-rm -fr $(OBJS_DIR)
	-rm -fr $(BONUS_OBJS_DIR)
=======
	@rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR) 2>/dev/null || true
>>>>>>> jm-test

fclean	: clean
	@echo "Full cleaning..."
	-make fclean -C libft
<<<<<<< HEAD
	-rm $(NAME)
	-rm $(BONUS_NAME)
=======
	@rm -f $(NAME) $(NAME_BONUS) 2>/dev/null || true
>>>>>>> jm-test

re		: fclean all

.PHONY : all clean fclean re bonus

-include $(DEPS)
