/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 21:01:53 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:42:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	free_dest(char **dst, int i)
{
	while (i <= 0)
	{
		free(dst[i]);
		i--;
	}
	free(dst);
}

static int	ft_strlen_sep(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

static char	*ft_strdup_sep(const char *s, char c)
{
	char	*dest;
	int		s_len;
	int		i;

	dest = 0;
	while (*s == c && *s)
		s++;
	s_len = ft_strlen_sep(s, c);
	dest = ft_calloc(s_len + 1, sizeof (char));
	if (!dest)
		return (0);
	i = -1;
	while (++i < s_len)
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

static int	count_words(char const *str, char c)
{
	int	count;

	if (!str)
		return (0);
	if (c == '\0')
		return (1);
	count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
			count++;
		while (*str != c && *str)
			str++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		len;
	int		i;

	len = count_words(s, c);
	if (!len || *s == '\0')
		return (ft_calloc(1, sizeof(char *)));
	dest = ft_calloc(len + 1, sizeof(char *));
	if (!dest)
		return (0);
	i = -1;
	while (++i < len)
	{
		while (*s == c && *s)
			s++;
		dest[i] = ft_strdup_sep(s, c);
		if (!dest[i])
		{
			free_dest(dest, i);
			return (0);
		}
		s += ft_strlen_sep(s, c);
	}
	dest[i] = 0;
	return (dest);
}
