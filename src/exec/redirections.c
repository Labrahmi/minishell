/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kdio <bel-kdio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:07:17 by bel-kdio          #+#    #+#             */
/*   Updated: 2023/06/19 14:37:57 by bel-kdio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	output(t_pre_tokens *out)
{
	int	out_file;

	while (out)
	{
		if (ft_strlen(out->content) == 0)
		{
			glob.exit_status = pr_err("minishell: ", out->content,
					": No such file or directory\n", 1);
			return 1;
		}
		if (out->type == TYPE_RED_OUT)
			out_file = open(out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (out->type == TYPE_RED_APP)
			out_file = open(out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
		{
			out = out->next;
			continue ;
		}
		if (out_file != -1)
		{	
                dup2(out_file, STDOUT_FILENO);
				 close(out_file);
		}
		else
		{
			if (access(out->content, R_OK) != 0)
            {
                glob.exit_status = pr_err("minishell: ", out->content,
                                          ": Permission denied\n", 1);
                return 1;
            }
			glob.exit_status = pr_err("minishell: ", out->content,
					": No such file or directory\n", 1);
		}
		out = out->next;
	}
	return (0);
}

int	input(t_pre_tokens *in)
{
	int	in_file;

	while (in)
	{
		if (ft_strlen(in->content) == 0)
		{
			glob.exit_status = pr_err("minishell: ", in->content,
					": No such file or directory\n", 1);
			return 1;
		}
		in_file = open(in->content, O_RDONLY);
		if (in_file != -1)
		{
            dup2(in_file, STDIN_FILENO);
            close(in_file);
		}
		else
		{
			if (access(in->content, R_OK) != 0)
            {
                glob.exit_status = pr_err("minishell: ", in->content,
                                          ": Permission denied\n", 1);
                return 1;
            }
			glob.exit_status = pr_err("minishell: ", in->content,
					": No such file or directory\n", 1);
		}
		in = in->next;
	}
	return (0);
}

int	redirection(t_command *head)
{
	t_pre_tokens	*out;
	t_pre_tokens	*in;
	int				ret;
	int				cmdn;
	
	ret = 0;
	cmdn = 0;
	if (head->herdoc_files)
	{
		dup2(head->pipe_hd, 0);
		close(head->pipe_hd);
	}
	out = head->output_files;
	in = head->input_files;
	if (head->output_files)
	{
		if (output(out))
			return (1);
		if (!head->cmd)
			cmdn = 2;
	}
	if (head->input_files)
	{
	ft_putstr_fd("hey", 2);
		if (input(in))
			return (1);
		if (!head->cmd)
			cmdn =2;
	}
	if(cmdn)
		return (2);
	return (0);
}
