/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 11:16:01 by csekakul          #+#    #+#             */
/*   Updated: 2026/03/06 08:06:24 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		fd1;
	char	*line;
	char	*line1;

	fd = open("test2.txt", O_RDONLY);
	fd1 = open("test.txt", O_RDONLY);
	if (fd < 0 || fd1 < 0)
	{
		printf("Invalid file decriptor.\n");
		return (1);
	}
	line = get_next_line(fd);
	line1 = get_next_line(fd1);
	while (line != NULL)
	{
		printf("line -> %s", line);
		free(line);
		line = get_next_line(fd);
	}
	while (line1 != NULL)
	{
		printf("line -> %s", line1);
		free(line1);
		line1 = get_next_line(fd1);
	}
	close(fd);
	return (0);
}
