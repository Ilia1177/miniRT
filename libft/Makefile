# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:27:51 by npolack           #+#    #+#              #
#    Updated: 2024/12/07 14:27:43 by npolack          ###   ########.fr        #
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
				get_next_line/get_next_line_utils_bonus.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
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

$(OBJS_DIR)/%.o	 		:$(SRCS_DIR)/%.c
	mkdir -p srcs/objs/ft_printf/
	mkdir -p srcs/objs/get_next_line/	
	$(CC) $(CFLAGS) -c $< -o $@

clean	:	
			make clean -C srcs

fclean	:	clean
			make fclean -C srcs
			$(RM) bin

re		:	fclean all


.PHONY	:	all clean fclean re bonus
