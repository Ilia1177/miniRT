# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:27:51 by npolack           #+#    #+#              #
#    Updated: 2024/12/07 13:48:42 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

BONUS_SRCS	=	lstnew		\
				lstadd_front\
				lstsize		\
				lstlast		\
				lstadd_back	\
				lstdelone	\
				lstclear	\
				lstiter		\
				lstmap

SRCS	=	ft_isspace.c	\
			ft_isalpha.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_strlen.c		\
			ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memmove.c	\
			ft_strlcpy.c	\
			ft_strlcat.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strnstr.c	\
			ft_atoi.c		\
			ft_calloc.c		\
			ft_strdup.c		\
		   	ft_substr.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c	\
			ft_striteri.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_strnlen.c

BONUS_SRCS := $(addsuffix _bonus.c, $(BONUS_SRCS))
BONUS_SRCS := $(addprefix ft_, $(BONUS_SRCS))

OBJS_DIR	= objs

OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

B_OBJS		=	$(BONUS_SRCS:%.c=$(OBJS_DIR)/%.o)

AR 			=	ar -rcs

CC			=	cc 

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

all				:	$(NAME) 

$(NAME)			:	$(OBJS) $(B_OBJS)
					$(AR) $(NAME) $^ 

$(OBJS_DIR)/%.o	: %.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:	
			$(RM) $(OBJS) $(B_OBJS)
			rm -rf $(OBJS_DIR)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
