/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:49:33 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/06/02 16:46:57 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int main(int argc, char const *argv[], char **env)
{
	t_pre_tokens	*head;
	t_user_data		data;
	t_env			*env_head;
	t_command		*head_command;
	char			***all_cmd;

	env_head = ft_set_env(env);
	while (1)
	{
		data.user_input = ft_read_input();
		head_command = get_first_command(data.user_input, env_head);
		ft_echo(&(head_command->args));
		// conver_l_args_to_p(head_command);
		// set_path(head_command, env);
		// all_cmd = convert_linked_list_to_tr_p(head_command);
		// exec(all_cmd, head_command, env);
		// // printf_commands(head_command);
		free_commands(&head_command);
		free(data.user_input);
		// usleep(50000);print_leaks();
	}
	return 0;
}
