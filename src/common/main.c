/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:49:33 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/06/20 15:56:10 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_globals	glob;

void	sigint_handler(int sig_num)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
	glob.exit_status = 1;
	signal(SIGINT, sigint_handler);
}

int	main(int ac, char *av[], char **env)
{
	t_user_data		data;
	t_env			*env_head;
	t_command		*head_command;
	char			***all_cmd;
	t_env			*export_head;
	int				is_built;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	env_head = ft_set_env(env);
	export_head = ft_set_env(env);
	glob.exit_status = 0;
	while (1)
	{
		data.user_input = ft_read_input();
		head_command = get_first_command(data.user_input, env_head);
		if (head_command)
		{
			// conver_l_args_to_p(head_command);
			// all_cmd = convert_linked_list_to_tr_p(head_command);
			// exec(all_cmd, head_command, export_head, env_head);
			printf_commands(head_command);
			free_commands(&head_command);
		}
		free(data.user_input);
		print_leaks();
	}
	return (0);
}

// int main(int argc, char const *argv[])
// {
// 	int	fd = open("out.txt", O_CREAT | O_RDONLY | O_WRONLY, 777);
// 	dup2(fd, STDOUT_FILENO);
// 	printf("Hello World 1\n");
// 	close(fd);
// 	return (0);
// }
