# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 15:24:59 by jhervoch          #+#    #+#              #
#    Updated: 2025/05/07 15:30:14 by jhervoch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=thread -g -O1 -fPIE #-fsanitize=address
	INCLUDES = -I/usr/include -I./mlx -I./libft/include -I./include
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm 
else
	CFLAGS = -g #-Wall -Wextra -Werror -g 
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
		handle_2\
		img\
		init\
		init_2\
		input\
		inter_cyl_utils\
		intersection\
		light\
		lst_cylinder\
		lst_light\
		lst_plane\
		lst_sphere\
		matrix\
		norm_utils\
		normal\
		parsing_utils\
		parsing_utils_2\
		print\
		ray\
		rgb\
		rotation_object\

SRCS_BONUS = 	minirt\
		init/build_scene\
		init/build_scene_utils\
		display/camera\
		canvas/canvas\
		utils/clean\
		display/color\
		display/color_2\
		utils/debug\
		display/dl_img\
		display/img\
		init/init\
		input/input\
		intersection/intersection\
		intersection/intersect_cylinder\
		intersection/intersect_sphere\
		intersection/intersect_plane\
		intersection/intersect_hyperboloid\
		intersection/intersect_triangle\
		display/light\
		list/lst_cylinder\
		list/lst_hyperboloid\
		list/lst_light\
		list/lst_plane\
		list/lst_sphere\
		list/lst_triangle\
		utils/matrix\
		init/norm_utils\
		intersection/normal\
		init/parsing_utils_2\
		init/parsing_utils\
		init/parsing_utils_option\
		utils/print\
		display/ray\
		display/text_checkerboard\
		display/text_img\
		utils/vector\

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
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJS_BONUS_DIR)/%.o: $(SRCS_BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $^ $(MLX_FLAGS) -o $(NAME) $(INCLUDES) -L./libft/bin -lft

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $^ $(MLX_FLAGS) -o $(NAME_BONUS) $(INCLUDES) -L./libft/bin -lft 

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
