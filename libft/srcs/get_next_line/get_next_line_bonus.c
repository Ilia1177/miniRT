/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:28:44 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 13:41:47 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

static char	*make_paragraph(char *paragraph, char *current_line);
static char	*get_characters(int fd, char *paragraph, char *buffer);
static char	*make_line(char *paragraph);

char	*get_next_line(int fd)
{
	static char		*paragraph[1024];
	char			*buffer;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	paragraph[fd] = get_characters(fd, paragraph[fd], buffer);
	if (!paragraph[fd])
		return (NULL);
	if (ft_strchr(paragraph[fd], '\n'))
	{
		line = make_line(paragraph[fd]);
		paragraph[fd] = make_paragraph(paragraph[fd], line);
	}
	else
	{
		line = ft_strdup(paragraph[fd]);
		free(paragraph[fd]);
		paragraph[fd] = 0;
	}
	return (line);
}

static char	*make_line(char *paragraph)
{
	char	*line;
	int		llen;
	int		i;

	llen = ft_strnlen(paragraph, '\n');
	line = malloc(sizeof(char) * (llen + 2));
	if (!line)
		return (0);
	i = 0;
	while (i < llen)
	{
		line[i] = paragraph[i];
		i++;
	}
	if (paragraph[i] == '\n')
	{
		line[i] = paragraph[i];
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

static char	*make_paragraph(char *paragraph, char *current_line)
{
	char	*tmp;
	ssize_t	para_len;
	ssize_t	line_len;
	ssize_t	new_plen;

	line_len = ft_strnlen(current_line, 0);
	para_len = ft_strnlen(paragraph, 0);
	if (line_len == para_len)
	{
		free(paragraph);
		paragraph = 0;
		return (NULL);
	}
	new_plen = para_len - line_len;
	tmp = paragraph;
	paragraph = ft_substr(tmp, line_len, new_plen);
	free(tmp);
	return (paragraph);
}

static char	*get_characters(int fd, char *paragraph, char *buffer)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!paragraph)
			paragraph = ft_strdup(buffer);
		else
		{
			tmp = paragraph;
			paragraph = ft_strjoin(tmp, buffer);
			free(tmp);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (paragraph);
}
