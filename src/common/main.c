/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:49:33 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/29 04:29:05 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int main(int argc, char const *argv[], char **env)
{
	t_pre_tokens	*head;
	t_user_data		data;
	t_env			*env_head;
	t_command		*head_command;

	env_head = ft_set_env(env);
	while (1)
	{
		data.user_input = ft_read_input();
		head_command = get_first_command(data.user_input, env_head);
		printf_commands(head_command);
		free_commands(&head_command);
		free(data.user_input);
		// print_leaks();
	}
	return 0;
}

// int main(int argc, char const *argv[])
// {
// 	int	fd = open("out.txt", O_CREAT | O_RDONLY | O_WRONLY, 777);
// 	dup2(fd, STDOUT_FILENO);
// 	printf("Hello World 1\n");
// 	close(fd);
// 	return 0;
// }
