/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:22:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/24 01:55:15 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *get_index(char *string)
{
	int	i;

	i = 0;
	while (string[i] && (ft_isalnum(string[i]) || string[i] == '_'))
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

int	is_valid_variable(char after_dollar)
{
	return ((ft_isalpha(after_dollar)) || (after_dollar == '_'));
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
			if (!((*token)[i + 1]))
				return ;
			else if (is_valid_variable((*token)[i + 1]))
			{
				new = get_new_token(token, new, head_env, i);
				(*token) = ft_strdup(new);
				free(new);
			}
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

int	set_up_remove_vars(int *j, int *in_single, int *in_double)
{
	*j = 0;
	*in_single = 0;
	*in_double = 0;
	return (-1);
}

char	*remove_quote(char *content)
{
	char	*copy;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	i = set_up_remove_vars(&j, &in_single, &in_double);
	copy = malloc(ft_strlen(content) + 1);
	while (content[++i])
	{
		if (content[i] == '\'' && !(in_double))
		{
			in_single = !(in_single);
			i++;
			continue;
		}
		if (content[i] == '\"' && !(in_single))
		{
			in_double = !(in_double);
			i++;
			continue;
		}
		else
		{
			copy[j] = content[i];
			j++;
		}
	}
	copy[j] = '\0';
	free(content);
	return (copy);
}

void ft_remove_quotes(t_pre_tokens **head, t_env *head_env)
{
	t_pre_tokens *node;

	node = *head;
	while (node)
	{
		node->content = expand_variable(node->content, head_env);
		node->content = remove_quote(node->content);
		node = node->next;
	}
}
