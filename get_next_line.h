/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:02:00 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/18 14:09:14 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Includes
# include <stdlib.h>
# include <unistd.h>

// Functions
char		*get_next_line(int fd);
size_t		ft_strlen(char *s);
char		*ft_strdup(char *s);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
void		fill_str(char *res, char *s1, char *s2);

#endif
