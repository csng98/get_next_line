/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:01:50 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/17 13:39:06 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s1)
		return (s2);
	len1 = strlen(s1);
	len2 = strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (free(s1), free(s2), NULL);
	memcpy(joined, s1, len1);
	memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (joined);
}

static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	memcpy(line, stash, i);
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new_stash = malloc(strlen(stash + i) + 1);
	if (!new_stash)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0) 
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), stash = NULL, NULL);
		buffer[bytes] = '\0';
		stash = join_and_free(stash, ft_strdup(buffer));
		if (!stash)
			return (NULL);
	}
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
