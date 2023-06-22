/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:19:47 by bel-kdio          #+#    #+#             */
/*   Updated: 2023/06/22 11:26:02 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	if_cmd_null_or_home(void)
{
	if (search_in_env(g_glob.env, "HOME"))
	{
		search_in_env_and_replace(g_glob.env, "OLDPWD", search_in_env(g_glob.env,
				"PWD"));
		search_in_env_and_replace(g_glob.export, "OLDPWD",
			search_in_env(g_glob.export, "PWD"));
		chdir(search_in_env(g_glob.env, "HOME"));
		search_in_env_and_replace(g_glob.env, "PWD", getcwd(NULL, 0));
		search_in_env_and_replace(g_glob.export, "PWD", getcwd(NULL, 0));
	}
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
}

int	exec_cd(t_command *cmd)
{
	if (access(cmd->db_args[0], F_OK) == 0)
	{
		search_in_env_and_replace(g_glob.env, "OLDPWD", search_in_env(g_glob.env,
				"PWD"));
		search_in_env_and_replace(g_glob.export, "OLDPWD",
			search_in_env(g_glob.export, "PWD"));
		chdir(cmd->db_args[0]);
		search_in_env_and_replace(g_glob.env, "PWD", getcwd(NULL, 0));
		search_in_env_and_replace(g_glob.export, "PWD", getcwd(NULL, 0));
	}
	else if (!cmd->db_args[0] || ft_strncmp(cmd->db_args[0], "~", 2) == 0)
	{
		if_cmd_null_or_home();
	}
	else
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		g_glob.exit_status = 1;
	}
	return (1);
}
