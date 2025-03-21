NAME = miniRT

UNAME = $(shell uname)
SRCS_DIR = srcs
OBJS_DIR = objs
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
CLONE = mlx

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -I./mlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm 
else
	INCLUDES = -I/opt/X11/include -I./mlx -I./libft/include -I./include
	MLX_FLAGS = -L./libft/bin -L./mlx -L/usr/X11/lib -lft -lmlx -lXext -lX11 -lm -framework OpenGL -framework AppKit
endif

LIBFT = libft/bin/libft.a

SRCS = 	miniRT.c\
		geo.c\
		img.c\
		input.c\

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror
CC = cc

all :  $(LIBFT) $(MLX_LIB) $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME) #-L./libft/bin -lft

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

re		: fclean all

.PHONY : all clean fclean re bonus
