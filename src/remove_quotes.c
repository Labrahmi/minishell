/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:22:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/21 20:54:47 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *get_index(char *string)
{
	int	i = 0;

	while (string[i] && string[i] != '\"' && string[i] != ' ')
		i++;
	return (ft_substr(string, 0, i));
}

char	*get_value(char *index, t_env **head_env)
{
	t_env	*node;

	node = *head_env;
	while (node)
	{
		if (ft_strncmp(index, node->index, ft_strlen(index)) == 0)
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (ft_strdup(""));
}

char	*expand_variables(char *token, t_env *head_env)
{
	int	in_single_quote = 0;
	int	i = 0;
	char *env_index;
	char *env_value;
	char *new_token;
	int	len_to;

	i = 0;
	new_token = NULL;
	while (token[i])
	{
		if (token[i] == '\'')
			in_single_quote = (!in_single_quote);
		if (token[i] == '$' && (!in_single_quote))
		{
			env_index = get_index(&token[i + 1]);
			env_value = get_value(env_index, &head_env);
			new_token = ft_substr(token, 0, i);
			new_token = ft_strjoin(new_token, env_value);
			len_to = ft_strlen(&token[i + 1]) - ft_strlen(env_index);
			new_token = ft_strjoin(new_token, ft_substr(&token[i + 1], ft_strlen(env_index), len_to));
			token = new_token;
		}
		i++;
	}
	if (!new_token)
		return (token);
	return (new_token);
}
/*
	minishell-1.0> "Hello $HOME From $PATH"
	
	token>>>>>>>>>>>>>> '"Hello $HOME From $PATH"'
	&token[i + 1]>>>>>> 'HOME From $PATH"'
	env_index>>>>>>>>>> 'HOME'
	env_value>>>>>>>>>> '/Users/macbook'
	new_token>>>>>>>>>> 'Hello '
*/

void ft_remove_quotes(t_pre_tokens **head, t_env *head_env)
{
	t_pre_tokens *node;

	node = *head;
	while (node)
	{
		node->content = expand_variables(node->content, head_env);
		node = node->next;
	}
}
