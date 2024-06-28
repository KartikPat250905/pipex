# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:05:34 by karpatel          #+#    #+#              #
#    Updated: 2024/06/26 17:10:44 by karpatel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCES = pipex.c pipex_utils.c
BSOURCES = dup_bonus.c execute_bonus.c pipex_bonus.c struct_pipes_bonus.c
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)
LIBDIR = ./libft

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $@ $(CFLAGS) $^ ./libft/libft.a

bonus: .bonus

.bonus: $(BOBJECTS)
	$(MAKE) -C $(LIBDIR)
	$(CC) -o $(NAME) $(CFLAGS) $^ ./libft/libft.a
	touch .bonus

$(SOURCE_DIR)/%.o: %.c
	$(CC) -I -c $(CFLAGS) $< -o $@

clean:
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(OBJECTS) $(BOBJECTS) .bonus

fclean: clean
	$(MAKE) -C $(LIBDIR) $@
	rm -f $(NAME)

re: fclean all

debug: re

.PHONY: debug all clean fclean re bonus
