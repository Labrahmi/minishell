# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:42:27 by ylabrahm          #+#    #+#              #
#    Updated: 2023/05/21 20:09:42 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	./src/main.c ./src/error.c \
		./src/colorize.c ./src/free_double.c \
		./src/pre_t.c ./src/remove_quotes.c \
		./src/set_env.c

OBJS = $(SRCS:.c=.o)

CC = cc

RM = rm -f

# CFLAGS = -Wall -Wextra -Werror
# -fsanitize=address

all:	$(NAME)

$(NAME):	$(SRCS) 
# @make -C ./inc/libft/
	$(CC) $(CFLAGS) ./inc/libft/libft.a $(SRCS) -lreadline -o $(NAME)

clean:
# @make clean -C ./inc/libft/
	$(RM) $(OBJS) 

fclean:	clean
# @make fclean -C ./inc/libft/
	$(RM) $(NAME)

re:	fclean all
