/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:02:00 by csekakul          #+#    #+#             */
/*   Updated: 2026/02/06 13:54:06 by csekakul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Includes
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// Structures
typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}									t_list;

// Functions

#endif
