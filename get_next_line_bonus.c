/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 09:21:26 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/13 16:19:07 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void    ft_lstclear(t_gnl_list **lst)
{
    t_gnl_list  *lastnode;
    int         i;
    int         k;
    char        *buf;

    buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return (ft_del(lst));
    lastnode = ft_lastnode(lst);
    i = 0;
    k = 0;
    while (lastnode->content[i] != '\0' && lastnode->content[i] != '\n')
        ++i;
    while (lastnode->content[i] != '\0' && lastnode->content[++i])
        buf[k++] = lastnode->content[i];
    buf[k] = '\0';
    ft_del(lst);
    ft_attach(lst, buf);
}

void    ft_attach(t_gnl_list **lst, char *buf)
{
    t_gnl_list  *new_node;
    t_gnl_list  *lastnode;

    if (!buf[0])
        return (free(buf));
    new_node = malloc(sizeof(t_gnl_list));
    if (!new_node)
    {
        free(buf);
        return (ft_del(lst));
    }
    lastnode = ft_lastnode(lst);
    if (!lastnode)
        *lst = new_node;
    else
        lastnode->next = new_node;
    new_node->content = buf;
    new_node->next = NULL;
}

char    *ft_newline(t_gnl_list **lst, char *line, int l_line)
{
    t_gnl_list  *temp;
    int         displacer;

    temp = *lst;
    displacer = 0;
    l_line += ft_contsize(temp);
    line = (char *)malloc(sizeof(char) * (l_line + 1));
    if (!line)
    {
        ft_del(lst);
        return (NULL);
    }
    displacer = ft_cpylst(temp, line, displacer);
    line[l_line] = '\0';
    return (line);
}

void    ft_lstnew(t_gnl_list **lst, int fd)
{
    int     char_read;
    char    *buf;

    char_read = 0;
    while (!found_newline(*lst))
    {
        buf = malloc(BUFFER_SIZE + 1);
        if (buf == NULL)
            return (ft_del(lst));
        char_read = read(fd, buf, BUFFER_SIZE);
        if (!char_read)
        {
            free(buf);
            return ;
        }
        buf[char_read] = '\0';
        ft_attach(lst, buf);
    }
}

char    *get_next_line(int fd)
{
    static t_gnl_list   *lst[FOPEN_MAX];
    char                *line;
    int                 l_line;

    line = NULL;
    l_line = 0;
    if (read(fd, &line, 0) < 0)
    {
        ft_del(&lst[fd]);
        return (NULL);
    }
    if (fd < 0 || fd > FOPEN_MAX - 1 || BUFFER_SIZE <= 0)
        return (NULL);
    ft_lstnew(&lst[fd], fd);
    if (lst[fd] == NULL)
        return (NULL);
    line = ft_newline(&lst[fd], line, l_line);
    if (lst[fd] == NULL)
        return (NULL);
    ft_lstclear(&lst[fd]);
    return (line);
}
