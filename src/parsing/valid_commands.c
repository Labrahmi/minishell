/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 04:26:41 by macbook           #+#    #+#             */
/*   Updated: 2023/05/29 05:51:16 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_returned_to_files(t_pre_tokens *returned)
{
	printf("returned : %s [%d]\n", returned->content, returned->type);
}

t_pre_tokens	*remove_redirection(t_pre_tokens *args, t_command *command, int *get_type)
{
	t_pre_tokens	*node;
	t_pre_tokens	*returned;

	node = command->args;
	while (node->next)
	{
		if (node->next == args)
		{
			*get_type = args->type;
			returned = node->next->next;
			free(node->next->content);
			free(node->next);
			node->next = returned->next;
			return (returned);
		}
		node = node->next;
	}
	return (0);
}

int	check_redirections(t_pre_tokens	**head, t_command *command)
{
	t_pre_tokens	*args;
	t_pre_tokens	*returned;
	int				get_type;

	args = *head;
	get_type = 0;
	while (args)
	{
		if (args->type != TYPE_ARG)
		{
			if (!(args->next))
				return (1);
			else
			{
				if (args->next->type != TYPE_ARG)
					return (1);
				returned = remove_redirection(args, command, &get_type);
				printf("ret : %s(%d)\n", returned->content, get_type);
				// add_returned_to_files(returned);
			}
		}
		args = args->next;
	}
	return (0);
}

int valid_commands(t_command **head_commands)
{
	int			ret;
	t_command	*command;

	ret = 0;
	command = *head_commands;
	while (command)
	{
		ret += check_redirections(&command->args, command);
		command = command->next;
	}
	if (ret != 0)
	{
		print_error("parsing error\n");
		free_commands(head_commands);
	}
	return (ret);
}