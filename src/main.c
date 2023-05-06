/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/06 18:50:46 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cnt(char *string)
{
	int	i;

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

char	**ft_read_input(char *user_input)
{
	char	*prompt;
	char	**returned;

	prompt = ft_colorize("minishell-1.0$ ", "green");
	user_input = readline(prompt);
	free(prompt);
	if (!(user_input))
		ft_error("Bad user input\n");
	add_history(user_input);
	returned = ft_split(user_input, ' ');
	return (returned);
}

void	printf_linked(t_pre_tokens *head)
{
	t_pre_tokens	*node;
	
	node = head;
	while (node)
	{
		printf("$%s$\n", node->content);
		node = node->next;
	}
}

int main(int argc, char const *argv[])
{
	t_pre_tokens	*token_h;
	t_user_data		usr_dt;
	int				i;
	int				j;

	while (1)
	{
		token_h = NULL;
		usr_dt.spl_inp = ft_read_input(usr_dt.user_input);
		i = 0;
		while (usr_dt.spl_inp[i])
		{
			add_pre_t(&token_h, usr_dt.spl_inp[i], i);
			i++;
		}
		free_double(usr_dt.spl_inp);
		{
			t_pre_tokens	*tok;
			t_pre_tokens	*new_head;
			int				wh_;
			char			*string;

			wh_ = 1;
			tok = token_h;
			new_head = NULL;
			while (tok)
			{
				if (!(ft_cnt(tok->content)))
					add_pre_t(&new_head, tok->content, -1);
				else
				{
					string = tok->content;
					tok = tok->next;
					while ((tok) && (!(ft_cnt(tok->content))))
					{
						string = ft_strjoin(string, tok->content);
						tok = tok->next;
					}
					if (tok)
						string = ft_strjoin(string, tok->content);
					add_pre_t(&new_head, string, -1);
				}
				if (tok)
					tok = tok->next;
			}
			printf_linked(new_head);
			exit(0);
		}
	}
	return 0;
}
