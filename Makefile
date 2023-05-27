# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:42:27 by ylabrahm          #+#    #+#              #
#    Updated: 2023/05/28 00:07:58 by ylabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = 	./src/main.c ./src/error.c \
		./src/colorize.c ./src/free_double.c \
		./src/pre_t.c ./src/remove_quotes.c \
		./src/set_env.c ./src/fill_commands.c \
		./src/lexer.c

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
