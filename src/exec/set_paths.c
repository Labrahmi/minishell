/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kdio <bel-kdio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:57:16 by bel-kdio          #+#    #+#             */
/*   Updated: 2023/06/22 16:00:19 by bel-kdio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_path(t_env *envp)
{
	int		i;
	char	**path;
	char	*trimmed;
	int		check;

	i = 0;
	check = 0;
	trimmed = search_in_env_and_return_value(envp, "PATH");
	if (!trimmed)
		return (NULL);
	path = ft_split(trimmed, ':');
	return (path);
}

char	*if_is_file(char *cmd)
{
	char		*path;
	struct stat	filestat;

	path = NULL;
	if (stat(cmd, &filestat) == 0)
	{
		if (!(filestat.st_mode & S_IFDIR))
			path = ft_strdup(cmd);
		else
			path = ft_strdup("dir");
	}
	return (path);
}

char	*if_not_file(char *cmd, t_env *env_head)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	paths = get_path(env_head);
	while (paths && paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (access(paths[i], F_OK | X_OK) != -1)
		{
			path = ft_strdup(paths[i]);
			break ;
		}
		else
			path = NULL;
		i++;
	}
	if (!paths)
		path = ft_strdup("not");
	free_double(paths);
	return (path);
}

char	*set_path(t_command *head_command)
{
	t_command	*tmp1;

	tmp1 = head_command;
	tmp1->path = ft_strdup("\0");
	if (!tmp1->cmd)
	{
		free(tmp1->path);
		tmp1->path = ft_strdup("cmdnull");
		return (tmp1->path);
	}
	if (check_if_buil(tmp1->cmd) == 0)
	{
		free(tmp1->path);
		if (access(tmp1->cmd, F_OK | X_OK) != -1)
			tmp1->path = if_is_file(tmp1->cmd);
		else
		{
			if (tmp1->cmd && ft_strchr(tmp1->cmd, '/'))
				tmp1->path = ft_strdup("not");
			else
				tmp1->path = if_not_file(tmp1->cmd, g_glob.env);
		}
	}
	return (tmp1->path);
}
