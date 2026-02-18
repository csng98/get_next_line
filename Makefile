# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csekakul <csekakul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 08:28:15 by csekakul          #+#    #+#              #
#    Updated: 2026/02/18 10:12:28 by csekakul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a

SOURCES = \
	get_next_line.c get_next_line_utils.c \

INCLUDE = -I.

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER) Makefile
	$(AR) $(NAME) $(OBJECTS) 

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE)/$(HEADER) -c $<

clean: Makefile
	rm -f $(OBJECTS)

fclean: clean Makefile
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
