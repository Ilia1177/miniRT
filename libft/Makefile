# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:27:51 by npolack           #+#    #+#              #
#    Updated: 2025/04/14 19:06:40 by jhervoch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	bin/libft.a

LIBFT		=	$(SRCS_DIR)/libft.a

SRCS_DIR	=	srcs
OBJS_DIR	=	srcs/objs

SRCS		=	ft_printf/ft_printf.c\
				ft_printf/ft_print_str.c\
				ft_printf/ft_print_char.c\
				ft_printf/ft_print_dec.c\
				ft_printf/ft_print_hex.c\
				ft_printf/ft_print_unsigned.c\
				ft_printf/ft_putnb_base.c\
				ft_printf/ft_print_address.c\
				ft_printf/ft_parse.c\
				ft_printf/get_intlen.c\
				get_next_line/get_next_line_bonus.c\
				get_next_line/get_next_line_utils_bonus.c\
				ft_vector/ft_cross_vector.c\
				ft_vector/ft_dist_vector.c\
				ft_vector/ft_div_vector.c\
				ft_vector/ft_dot_vector.c\
				ft_vector/ft_mag_vector.c\
				ft_vector/ft_mult_vector.c\
				ft_vector/ft_normalize_vector.c\
				ft_vector/ft_sub_vector.c\
				ft_vector/ft_add_vector.c\
				matrix/mat_adjugate.c\
				matrix/mat_apply.c\
				matrix/mat_compose.c\
				matrix/mat_init.c\
				matrix/mat_inverse.c\
				matrix/mat_orthogonal.c\
				matrix/mat_transform.c\
				matrix/mat_transpose.c\
				ft_argb/argb_toint.c\
				ft_argb/argb_ease.c\
				ft_argb/argb_clamp.c\
				ft_argb/argb_mult.c\
				ft_argb/argb_add.c\
				ft_argb/argb_inverse.c\
				ft_argb/argb_fromint.c\
				ft_argb/argb_applyalpha.c\
				ft_utils/ft_clamp.c

SRCS 		:= $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
TEST_SRCS	=	srcs/main_test.c
TEST_OBJS	= 	$(TEST_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

AR 			=	ar -rcs
CC			=	cc 
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

all				:	$(NAME) 

$(NAME)			:	$(OBJS) $(LIBFT)
					mkdir -p bin
					cp $(LIBFT) $(NAME)
					$(AR) $(NAME) $(OBJS)

$(LIBFT)	:  
		make -C srcs

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test	: $(TEST_OBJS) $(NAME) 
		$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -Lbin -lft -lm -o test
		
clean	:
			rm -f test
			make clean -C srcs

fclean	:	clean
			make fclean -C srcs
			$(RM) bin

re		:	fclean all


.PHONY	:	all clean fclean re bonus
