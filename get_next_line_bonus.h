/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:22:34 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/13 16:26:54 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_gnl_list
{
    char                *content;
    struct s_gnl_list   *next;
}                       t_gnl_list;

char        *get_next_line(int fd);
void        ft_attach(t_gnl_list **lst, char *buf);
char        *ft_newline(t_gnl_list **lst, char *line, int l_line);
void        ft_lstclear(t_gnl_list **lst);
void        ft_lstnew(t_gnl_list **lst, int fd);
t_gnl_list  *ft_lastnode(t_gnl_list **lst);
int         found_newline(t_gnl_list *lst);
int         ft_contsize(t_gnl_list *temp);
int         ft_cpylst(t_gnl_list *temp, char *line, int displacer);
void        ft_del(t_gnl_list **lst);

#endif