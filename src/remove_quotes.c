/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:22:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/22 23:19:22 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *get_index(char *string)
{
	int	i = 0;

	while (string[i] && string[i] != '\"' && string[i] != '\'' && string[i] != ' ')
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

void	four_free(char **token, char **suffix, char **env_index, char **env_value)
{
	if (*token)
		free(*token);
	if (*suffix)
		free(*suffix);
	if (*env_index)
		free(*env_index);
	if (*env_value)
		free(*env_value);
}

char	*get_new_token(char **token, char *new, t_env *head_env, int i)
{
	char	*env_index;
	char	*env_value;
	int		len_to;
	char	*suffix;

	env_index = get_index(&(*token)[i + 1]);
	env_value = get_value(env_index, &head_env);
	new = ft_substr((*token), 0, i);
	new = ft_strjoin(new, env_value);
	len_to = ft_strlen(&(*token)[i + 1]) - ft_strlen(env_index);
	suffix = ft_substr(&(*token)[i + 1], ft_strlen(env_index), len_to);
	new = ft_strjoin(new, suffix);
	four_free(token, &suffix, &env_index, &env_value);
	return (new);
}

void	expand_loop(char **token, int in_single_quote, int in_double_quote, int i, t_env *head_env)
{

	char	*new;

	new = NULL;
	while ((*token)[++i])
	{

		if (((*token)[i] == '\'') && (!in_double_quote))
			in_single_quote = (!in_single_quote);
		if (((*token)[i] == '\"') && (!in_single_quote))
			in_double_quote = (!in_double_quote);
		if ((*token)[i] == '$' && (!in_single_quote))
		{
			new = get_new_token(token, new, head_env, i);
			// env_index = get_index(&(*token)[i + 1]);
			// env_value = get_value(env_index, &head_env);
			// new = ft_substr((*token), 0, i);
			// new = ft_strjoin(new, env_value);
			// len_to = ft_strlen(&(*token)[i + 1]) - ft_strlen(env_index);
			// suffix = ft_substr(&(*token)[i + 1], ft_strlen(env_index), len_to);
			// new = ft_strjoin(new, suffix);
			(*token) = ft_strdup(new);
			free(new);
		}
	}
}

char	*expand_variable(char *token, t_env *head_env)
{
	int in_single_quote;
	int in_double_quote;
	int	i;

	i = -1;
	in_single_quote = 0;
	in_double_quote = 0;
	expand_loop(&token, in_single_quote, in_double_quote, i, head_env);
	return (token);
}

void ft_remove_quotes(t_pre_tokens **head, t_env *head_env)
{
	t_pre_tokens *node;

	node = *head;
	while (node)
	{
		node->content = expand_variable(node->content, head_env);
		node = node->next;
	}
}
