/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:12:22 by csekakul          #+#    #+#             */
/*   Updated: 2026/03/13 13:58:44 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*set_line(char *line_buffer)
{
	char	*left_chars;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (0);
	left_chars = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left_chars == 0)
	{
		free(left_chars);
		left_chars = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_chars);
}

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

static char	*fill_line_buffer(int fd, char *left_chars, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(left_chars);
			return (0);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!left_chars)
			left_chars = ft_strdup("");
		tmp = left_chars;
		left_chars = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_chars);
}

char	*get_next_line(int fd)
{
	static char	*left_chars[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
	{
		free(left_chars[fd]);
		free(buffer);
		left_chars[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, left_chars[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_chars[fd] = set_line(line);
	return (line);
}
