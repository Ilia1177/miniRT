/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:35:12 by npolack           #+#    #+#             */
/*   Updated: 2024/10/30 20:54:12 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>
# include "ft_printf.h"
# include "get_next_line_bonus.h"

///////////// PART 1 ///////////////////////////////////////////////////////////

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
//	set memory (*s) with a value (c) on n bytes
void	*ft_memset(void *s, int c, size_t n);
//	set memory with NULL on n bytes
void	ft_bzero(void *s, size_t n);
//	copy memory on n bytes
void	*ft_memcpy(void *dest, const void *src, size_t n);
//	copy overlaping memory (or not)
void	*ft_memmove(void *dest, const void *src, size_t n);
//	copy src to dst on size max
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//	append src to dst on size max
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
//	find first occurence of c in *s
char	*ft_strchr(const char *s, int c);
//	find last (right) occurence of c in *s
char	*ft_strrchr(const char *s, int c);
//	compare string on n bytes
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
//	look for c in s on n bytes
void	*ft_memchr(const void *s, int c, size_t n);
//	compare memory on n bytes
int		ft_memcmp(const void *s1, const void *s2, size_t n);
//	find little in big on len bytes
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);

//added after moulinette
float	ft_strtof(char *str, char **end);
///////////// PART 2 ///////////////////////////////////////////////////////////

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

///////////// BONUS! ///////////////////////////////////////////////////////////

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	char			*name;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
