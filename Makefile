NAME = miniRT
NAME_BONUS = Hazardous_miniRT

UNAME = $(shell uname)
SRCS_DIR = srcs
SRCS_BONUS_DIR = srcs_bonus
OBJS_DIR = objs
OBJS_BONUS_DIR = objs_bonus
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
CLONE = mlx

ifeq ($(shell uname), Linux)
	CFLAGS = -g -Wall -Wextra -Werror -g #-fsanitize=address
	INCLUDES = -I/usr/include -I./mlx -I./libft/include -I./include
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm 
else
	CFLAGS = -g  #-Wall -Wextra -Werror -g 
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
		handle\
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
		parsing_utils_2\
		print\
		ray\
		rotation_object\
		dl_img\
		matrix\

SRCS_BONUS = 	miniRT\
		build_scene\
		camera\
		camera_move\
		canvas\
		clean\
		color\
		debug\
		img\
		init\
		input\
		intersection\
		th_painter\
		intersect_cylinder\
		intersect_sphere\
		intersect_plane\
		intersect_hyperboloid\
		intersect_triangle\
		light\
		lst_cylinder\
		lst_light\
		lst_plane\
		lst_sphere\
		lst_triangle\
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

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS = $(OBJS:%.o=%.d)

OBJS_BONUS = $(SRCS_BONUS:$(SRCS_BONUS_DIR)/%.c=$(OBJS_BONUS_DIR)/%.o)
DEPS_BONUS = $(OBJS_BONUS:%.o=%.d)

CC = cc -MMD 

all : $(LIBFT) $(MLX_LIB) $(NAME)

bonus :  $(LIBFT) $(MLX_LIB) $(NAME_BONUS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJS_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
	mkdir -p $(OBJS_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME) -L./libft/bin -lft

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
	@rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR) 2>/dev/null || true

fclean	: clean
	@echo "Full cleaning..."
	-make fclean -C libft
	@rm -f $(NAME) $(NAME_BONUS) 2>/dev/null || true

re		: fclean all

.PHONY : all clean fclean re bonus

-include $(DEPS)
-include $(DEPS_BONUS)
