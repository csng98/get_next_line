/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:01:50 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/06 13:52:56 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

char	*get_buffer(int fd, char *buffer)
{
	int		fd;
	char	*buffer;

	buffer = malloc((ft_strlen(buffer) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read(fd, &buffer, 5);
	
}

char	*get_next_line(int fd)
{
	char	*line;

	if (line == NULL)
		
	return (line);
}

int	main(void)
{
	int	fd;
	int	buffer_size;

	fd = open("lorem.txt", O_RDONLY);
	buffer_size = 5;
	get_next_line();
}
