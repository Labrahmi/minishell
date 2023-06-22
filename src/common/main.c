/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:49:33 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/06/22 11:32:40 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_globals	g_glob;

void	void_fun(int ac, char *av[])
{
	(void) ac;
	(void) av;
}

void	sigint_handler(int sig_num)
{
	(void) sig_num;

	g_glob.exit_status = 1;
	write(1, "\n", 1);
	if (g_glob.in_herdoc == 1)
	{
		g_glob.in_herdoc = 3;
		close(0);
	}
	else
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char *av[], char **env)
{
	t_user_data		data;
	t_env			*env_head;
	t_command		*head_command;
	char			***all_cmd;
	t_env			*export_head;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	void_fun(ac, av);
	g_glob.dup = dup(0);
	env_head = ft_set_env(env);
	export_head = ft_set_env(env);
	g_glob.exit_status = 0;
	g_glob.in_herdoc = 0;
	g_glob.env = ft_set_env(env);
	g_glob.export = ft_set_env(env);
	while (1)
	{
		dup2(g_glob.dup, 0);
		data.user_input = ft_read_input();
		head_command = get_first_command(data.user_input, env_head);
		if (head_command)
		{
			conver_l_args_to_p(head_command);
			all_cmd = convert_linked_list_to_tr_p(head_command);
			exec(all_cmd, head_command);
			// printf_commands(head_command);
			free_commands(&head_command);
		}
		free(data.user_input);
	}
	return (0);
}
