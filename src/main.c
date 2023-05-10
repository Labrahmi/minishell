/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/10 20:08:20 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	prompt = ft_colorize("minishell-1.0> ", "green");
	user_input = readline(prompt);
	free(prompt);
	if (!(user_input))
		ft_error("Bad user input\n");
	add_history(user_input);
	trimed_value = ft_strtrim(user_input, " \t");
	free(user_input);
	return (trimed_value);
}

void printf_linked(t_pre_tokens *head)
{
	t_pre_tokens *node;
	int i;

	node = head;
	i = 0;
	while (node)
	{
		printf("token[%d(len:%zu)] : %s\n", i++, ft_strlen(node->content), node->content);
		node = node->next;
	}
}

void	sub_and_add(char *user_input, int start, int end, t_pre_tokens **head)
{
	char	*sub;

	sub = ft_substr(user_input, start, end - start);
	add_pre_t(head, sub);
	free(sub);
}

int	is_symbol(char symbol)
{
	if (symbol == '|' || symbol == '>' || symbol == '<')
		return (1);
	return (0);
}

void	add_symbol(t_pre_tokens **head, char *user_input, int start, int *end)
{
	char	*symbole_to_add;

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
	add_pre_t(head, symbole_to_add);
	free(symbole_to_add);
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

t_pre_tokens *ft_tokenizer(char *user_input)
{
	int 			in_double_quotes;
	int 			in_quotes;
	t_pre_tokens 	*head;
	int 			start;
	int 			end;

	end = 0;
	start = 0;
	in_quotes = 0;
	in_double_quotes = 0;
	head = NULL;
	while (user_input[end] != '\0')
	{
		if (user_input[end] == '"' && !(in_quotes))
		{
			in_double_quotes = !(in_double_quotes);
		}
		else if (user_input[end] == '\'' && !(in_double_quotes))
		{
			in_quotes = !(in_quotes);
		}
		if (!(in_quotes) && !(in_double_quotes))
		{
			if (user_input[end] == ' ')
			{
				sub_and_add(user_input, start, end, &head);
				start = end + 1;
			}
			if (is_symbol(user_input[end]))
			{
				add_symbol(&head, user_input, start, &end);
				start = end + 1;
			}
		}
		end++;
	}
	sub_and_add(user_input, start, end, &head);
	return (head);
}

int main(int argc, char const *argv[])
{
	t_pre_tokens	*head;
	t_user_data		data;

	while (1)
	{
		data.user_input = ft_read_input();
		head = ft_tokenizer(data.user_input);
		printf_linked(head);
		free_linked(&head);
		free(data.user_input);
	}
	return 0;
}


// echo "hey">>ls
// 0123456789ABCD