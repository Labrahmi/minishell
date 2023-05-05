# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:42:27 by ylabrahm          #+#    #+#              #
#    Updated: 2023/05/05 16:38:07 by ylabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	./src/main.c ./src/error.c \
		./src/colorize.c ./src/free_double.c \
		./src/pre_t.c

OBJS = $(SRCS:.c=.o)

CC = cc

RM = rm -f

# CFLAGS = -Wall -Wextra -Werror
# -fsanitize=address

all:	$(NAME)

$(NAME):	$(OBJS) 
	@make -C ./inc/libft/
	$(CC) $(CFLAGS) ./inc/libft/libft.a $(OBJS) -lreadline -o $(NAME)

clean:
	@make clean -C ./inc/libft/
	$(RM) $(OBJS) 

fclean:	clean
	@make fclean -C ./inc/libft/
	$(RM) $(NAME)

re:	fclean all
