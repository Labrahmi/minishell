/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:50:51 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/28 00:47:34 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_lexer(t_command **head)
{
	t_command		*f_cmd;
	t_pre_tokens	*temp_next;

	f_cmd = *head;
	while (f_cmd)
	{
		temp_next = f_cmd->args->next;
		f_cmd->cmd = ft_strdup(f_cmd->args->content);
		free(f_cmd->args->content);
		free(f_cmd->args);
		f_cmd->args = temp_next;
		f_cmd = f_cmd->next;
	}
}
