/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/05 20:18:26 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cnt(char *string, char searched)
{
	int	i;

	i = 0;
	if (!(string))
		ft_error("Something goes wrong\n");
	while (string[i])
	{
		if (string[i] == searched)
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

int main(int argc, char const *argv[])
{
	t_pre_tokens	*pre_token_head;
	t_user_data		usr_dt;
	int				i;
	int				j;

	// pre_token_head = malloc(sizeof(t_pre_tokens));
	while (1)
	{
		pre_token_head = NULL;
		usr_dt.spl_inp = ft_read_input(usr_dt.user_input);
		i = 0;
		while (usr_dt.spl_inp[i])
		{
			if (ft_cnt(usr_dt.spl_inp[i], '\"'))
			{
				printf("%s\n", ft_colorize(usr_dt.spl_inp[i], "red"));
			}
			else
			{
				printf("%s\n", ft_colorize(usr_dt.spl_inp[i], "green"));
			}
			i++;
		}
		free_double(usr_dt.spl_inp);
	}
	return 0;
}
