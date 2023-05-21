/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:43:06 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/21 00:53:17 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

enum token_type
{
	_CMD,
	_SYM,
	_ARG,
	_FLG,
};

typedef struct s_env
{
	char			*index;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_check_arg
{
	int		i;
	char	*stack;
	int		top;
	int		s_quote;
	int		d_quote;
	char	*content;
}	t_check_arg;

typedef struct s_pre_tokens
{
	char				*content;
	enum token_type		type;
	struct s_pre_tokens	*next;
}	t_pre_tokens;

typedef struct tokenizer_s
{
	int 			in_double_quotes;
	char			*user_input;
	int 			in_quotes;
	t_pre_tokens 	*head;
	int 			start;
	int 			end;
}	tokenizer_t;

typedef struct s_user_data
{
	char	**spl_inp;
	char	*user_input;
}   t_user_data;

void			ft_error(char *message);
void    		free_double(char **array);
char    		*ft_colorize(char *message, char *color);
int				add_pre_t(t_pre_tokens **head, char *content);
void			free_linked(t_pre_tokens **head);
void			ft_remove_quotes(t_pre_tokens **head, t_env *head_env);
t_env			*ft_set_env(char **env);


