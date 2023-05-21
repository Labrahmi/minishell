/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:22:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/21 01:19:27 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #include <stddef.h>

int ft_strchr_int(const char *str, int c)
{
    char ch = (char)c;

    while (*str != '\0')
    {
        if (*str == ch)
            return 1;
        str++;
    }
    if (ch == '\0')
        return 1;

    return 0;
}

char *remove_quotes(char *token, t_env *head_env)
{
	char *result = NULL;

	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		// Remove single quotes
		result = ft_strdup(token + 1);
		result[ft_strlen(result) - 1] = '\0';
	}
	else if (token[0] == '"' && token[ft_strlen(token) - 1] == '"')
	{
		// Remove double quotes
		result = ft_strdup(token + 1);
		result[ft_strlen(result) - 1] = '\0';
	}
	else if (token[0] == '$' && !ft_strchr_int(token, '\''))
	{
		// Lookup variable value in head_env
		char *var = token + 1; // Skip '$' symbol
		t_env *env_node = head_env;
		while (env_node != NULL)
		{
			if (ft_strncmp(env_node->index, var, ft_strlen(env_node->index)) == 0)
			{
				result = ft_strdup(env_node->value);
				break;
			}
			env_node = env_node->next;
		}
	}

	// If result is still NULL, no modifications needed
	if (result == NULL)
		result = ft_strdup(token);

	return result;
}

char	*remove_quotes(char *token, t_env *head_env)
{
	// code here
}

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
