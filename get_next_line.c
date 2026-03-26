/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:01:50 by csekakul          #+#    #+#             */
/*   Updated: 2026/03/26 09:14:21 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_stash(char *stash)
{
	char	*new_stash;
	char	*newline;
	int		len;

	newline = ft_strchr(stash, '\n');
	if (!newline)
	{
		new_stash = NULL;
		return (ft_free(&stash));
	}
	else
		len = (newline - stash) + 1;
	if (!stash[len])
		return (ft_free(&stash));
	new_stash = ft_substr(stash, len, ft_strlen(stash) - len);
	ft_free(&stash);
	if (!new_stash)
		return (NULL);
	return (new_stash);
}

char	*new_line(char *stash)
{
	char	*line;
	char	*newline;
	int		len;

	if (!stash)
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (newline)
		len = (newline - stash) + 1;
	else
		len = ft_strlen(stash);
	line = ft_substr(stash, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_buf(int fd, char *stash)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&stash));
	buffer[0] = '\0';
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = join_and_free(stash, buffer);
			if (!stash)
				return (NULL);
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((stash && !ft_strchr(stash, '\n')) || !stash)
		stash = read_buf (fd, stash);
	if (!stash)
		return (NULL);
	line = new_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = clean_stash(stash);
	return (line);
}
