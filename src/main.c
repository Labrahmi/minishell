/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/10 15:43:08 by ylabrahm         ###   ########.fr       */
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

t_pre_tokens *ft_tokenizer(char *user_input)
{
	int 			in_double_quotes;
	int 			in_quotes;
	t_pre_tokens 	*head;
	int 			start;
	char 			*sub;
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
				sub = ft_substr(user_input, start, end - start);
				add_pre_t(&head, sub);
				start = end + 1;
			}
		}
		end++;
	}
	add_pre_t(&head, &(user_input[start]));
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
		free(data.user_input);
	}
	return 0;
}
