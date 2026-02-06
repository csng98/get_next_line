/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:01:50 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/06 12:02:06 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t read(int fildes, void *buf, size_t nbyte)

char	*get_buffer(int fd, char *buffer)
{
	read(fd, buffer, 5);
}

char	*get_next_line(int fd)
{
	return (line);
}

int	main(void)
{
	int	fd;
	int	buffer_size;

	fd = open("lorem.txt", O_RDONLY);
	buffer_size = 5;
}
