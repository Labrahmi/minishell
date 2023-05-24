/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/24 17:03:40 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_leaks()
{
	printf("\n\n");
	printf("-----------[Leaks]-----------\n");
	system("leaks minishell | grep -A20 'leaks Report Version: 4.0'");
}

int ft_cnt(char *string)
{
	int i;

	i = 0;
	if (!(string))
		ft_error("Something goes wrong\n");
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char *ft_read_input()
{
	char *prompt;
	char *user_input;
	char *trimed_value;

	prompt = ft_colorize("monoshell-1.0> ", "green");
	user_input = readline(prompt);
	free(prompt);
	if (!(user_input))
		ft_error(NULL);
	add_history(user_input);
	trimed_value = ft_strtrim(user_input, " \t");
	free(user_input);
	return (trimed_value);
}

void printf_linked(t_pre_tokens *head)
{
	t_pre_tokens	*node;
	int				i;

	node = head;
	i = 0;
	while (node)
	{
		printf("[%d] : %s\n", ++i, node->content);
		node = node->next;
	}
}

void printf_env(t_env *head)
{
	t_env	*node;

	node = head;
	while (node)
	{
		printf("%s=%s\n", node->index, node->value);
		node = node->next;
	}
}

int	sub_and_add(char *user_input, int start, int end, t_pre_tokens **head)
{
	char	*sub;
	int		ret;

	ret = 0;
	sub = ft_substr(user_input, start, end - start);
	ret = add_pre_t(head, sub);
	free(sub);
	return (ret);
}

int	is_symbol(char symbol)
{
	if (symbol == '|' || symbol == '>' || symbol == '<')
		return (1);
	return (0);
}

int	add_symbol(t_pre_tokens **head, char *user_input, int start, int *end)
{
	char	*symbole_to_add;
	int		ret;

	sub_and_add(user_input, start, *end, head);
	symbole_to_add = malloc(3);
	symbole_to_add[0] = user_input[*end];
	symbole_to_add[1] = '\0';
	if (user_input[*end + 1])
	{
		if (user_input[*end] == '>' && user_input[*end + 1] == '>')
		{
			symbole_to_add[1] = '>';
			symbole_to_add[2] = '\0';
			(*end)++;
		}
		if (user_input[*end] == '<' && user_input[*end + 1] == '<')
		{
			symbole_to_add[1] = '<';
			symbole_to_add[2] = '\0';
			(*end)++;
		}
	}
	ret = add_pre_t(head, symbole_to_add);
	free(symbole_to_add);
	return (ret);
}

void	free_linked(t_pre_tokens **head)
{
	t_pre_tokens	*node;
	t_pre_tokens	*next;

	node = *head;
	while (node)
	{
		next = node->next;
		free(node->content);
		free(node);
		node = next;
	}
}

void *ft_init_zeros(tokenizer_t *tok)
{
	tok->end = 0;
	tok->start = 0;
	tok->in_quotes = 0;
	tok->in_double_quotes = 0;
	return (NULL);
}

int	ft_tokenizer_loop(tokenizer_t *tok)
{
	int	ret;

	ret = 0;
	while (tok->user_input[tok->end] != '\0')
	{
		if (tok->user_input[tok->end] == '\"' && !(tok->in_quotes))
			tok->in_double_quotes = !(tok->in_double_quotes);
		if (tok->user_input[tok->end] == '\'' && !(tok->in_double_quotes))
			tok->in_quotes = !(tok->in_quotes);
		if (!(tok->in_quotes) && !(tok->in_double_quotes))
		{
			if (tok->user_input[tok->end] == ' ')
			{
				ret += sub_and_add(tok->user_input, tok->start, tok->end, &tok->head);
				tok->start = tok->end + 1;
			}
			if (is_symbol(tok->user_input[tok->end]))
			{
				ret += add_symbol(&tok->head, tok->user_input, tok->start, &tok->end);
				tok->start = tok->end + 1;
			}
		}
		(tok->end)++;
	}
	ret += sub_and_add(tok->user_input, tok->start, tok->end, &tok->head);
	return (ret);
}

t_pre_tokens *ft_tokenizer(char *user_input)
{
	tokenizer_t	tok;
	char		*error;

	tok.head = ft_init_zeros(&tok);
	tok.user_input = ft_strdup(user_input);
	if (ft_tokenizer_loop(&tok) != 0)
	{
		free_linked(&(tok.head));
		error = ft_colorize("Error: missing quote\n", "red");
		printf("%s", error);
		free(error);
		free(tok.user_input);
		return (NULL);
	}
	free(tok.user_input);
	return (tok.head);
}

int main(int argc, char const *argv[], char **env)
{
	t_pre_tokens	*head;
	t_user_data		data;
	t_env			*env_head;

	env_head = ft_set_env(env);
	while (1)
	{
		data.user_input = ft_read_input();
		head = ft_tokenizer(data.user_input);
		ft_remove_quotes(&head, env_head);
		printf_linked(head);
		free_linked(&head);
		free(data.user_input);
		print_leaks();
	}
	return 0;
}
