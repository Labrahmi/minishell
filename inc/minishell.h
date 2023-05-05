/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:43:06 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/05 20:18:39 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// echo "wsup thats how we are worki fhe feij"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_user_data
{
	char	**spl_inp;
	char	*user_input;
}   t_user_data;

typedef struct s_pre_tokens
{
	char				*content;
	struct s_pre_tokens	*next;
}	t_pre_tokens;

void			ft_error(char *message);
void    		free_double(char **array);
char    		*ft_colorize(char *message, char *color);
int				add_pre_t(t_pre_tokens **head, char *content);