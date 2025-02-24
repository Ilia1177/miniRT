/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:28:49 by npolack           #+#    #+#             */
/*   Updated: 2024/10/29 12:37:58 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include "libft.h"

///////////////////////////// BONUS ////////////////////////////////////////////
//	gnl.c
char	*get_next_line(int fd);
//	gnl.utils.c
int		ft_strnlen(const char *str, int c);

#endif
