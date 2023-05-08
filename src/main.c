/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:43:08 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/08 16:38:16 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	t_user_data	data;
	int			i;
	int			j;

	while (1)
	{
		data.spl_inp = ft_read_input(data.user_input);
		free(data.spl_inp);
	}
	return 0;
}
