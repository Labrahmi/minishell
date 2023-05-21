/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:22:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/21 01:53:18 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *absolute_token(char *string)
{
	int	i = 0;

	while (string[i] && string[i] != '\"' && string[i] != ' ')
		i++;
	return (ft_substr(string, 0, i));
}

char	*real_value(char *ab, t_env **head_env)
{
	t_env	*node;

	node = *head_env;
	while (node)
	{
		if (ft_strncmp(ab, node->index, ft_strlen(ab)) == 0)
			return (ft_strdup(node->value));
		node = node->next;
	}
	return ft_strdup("");
}

char	*remove_quotes(char *token, t_env *head_env)
{
	int	in_single_quote = 0;
	int	i = 0;

	while (token[i])
	{
		if (token[i] == '\'')
			in_single_quote = (!in_single_quote);
		if (token[i] == '$' && (!in_single_quote))
		{
			char *ab = absolute_token(&token[i + 1]);
			char *pre = ft_strdup(token);
			pre[i] = '\0';
			char *vlue = real_value(ab, &head_env);
			char *res = ft_strjoin(pre, vlue);
			res = ft_strjoin(res, token + i + ft_strlen(ab) + 1);
			printf(">>>>>%s\n", res);
			exit(0);
		}
		i++;
	}
	// code here
	return 0;
}
// "echo hello world $HOME from our string"
// "echo hello world 
// youssef $HOME $PATH $LOGNAME

void ft_remove_quotes(t_pre_tokens **head, t_env *head_env)
{
	t_pre_tokens *node;

	node = *head;
	while (node)
	{
		node->content = remove_quotes(node->content, head_env);
		node = node->next;
	}
}
