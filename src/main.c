/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/08 22:39:38 by ylabrahm         ###   ########.fr       */
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

	prompt = ft_colorize("minishell-1.0$ ", "green");
	user_input = readline(prompt);
	free(prompt);
	if (!(user_input))
		ft_error("Bad user input\n");
	add_history(user_input);
	return (ft_strtrim(user_input, " \t"));
}

void printf_linked(t_pre_tokens *head)
{
	t_pre_tokens *node;

	node = head;
	while (node)
	{
		printf("%s\n", node->content);
		node = node->next;
	}
}

t_pre_tokens	*ft_tokenizer(char *user_input)
{
	int 			in_double_quotes;
	int 			in_quotes;
	t_pre_tokens	*head;
	int 			i;
	int				j;

	i = 0;
	j = 0;
	in_quotes = 0;
	in_double_quotes = 0;
	head = NULL;
	while (user_input[i] != '\0')
	{
		if (user_input[i] == '"' && !in_double_quotes)
		{
			in_quotes = !in_quotes;
			i++;
			continue ;
		}
		else if (user_input[i] == '\'' && !in_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue ;
		}
		if (!in_quotes && !in_double_quotes && user_input[i] == ' ')
		{
			user_input[i] = '\0';
			add_pre_t(&head, &(user_input[j]));
			j = i + 1;
		}
		i++;
	}
	add_pre_t(&head, &(user_input[j]));
	return (head);
}

int main(int argc, char const *argv[])
{
	t_pre_tokens	*head;
	t_user_data 	data;

	while (1)
	{
		data.user_input = ft_read_input();
		head = ft_tokenizer(data.user_input);
		printf_linked(head);
	}
	return 0;
}
