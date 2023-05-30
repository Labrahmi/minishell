/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 04:26:41 by macbook           #+#    #+#             */
/*   Updated: 2023/05/29 19:27:01 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// char	*remove_redirection(t_pre_tokens *args, t_command *command, int *ret_type)
// {
// 	t_pre_tokens	*node;
// 	t_pre_tokens	*returned;
// 	char			*ret_content;
// 	node = command->args;
// 	while (node->next)
// 	{
// 		if (node->next == args)
// 		{
// 			*ret_type = args->type;
// 			returned = node->next->next;
// 			free(node->next->content);
// 			free(node->next);
// 			node->next = returned->next;
// 			ret_content = ft_strdup(returned->content);
// 			free(returned->content);
// 			free(returned);
// 			return (ret_content);
// 		}
// 		node = node->next;
// 	}
// 	return (0);
// }

void	add_red_to_command(t_command **command_ix, t_pre_tokens **dest_ix, char *data)
{
	t_command	*command;
	t_pre_tokens	*dest;
	t_pre_tokens	*temp_dest;
	t_pre_tokens	*new_token;

	dest = *dest_ix;
	command = *command_ix;
	new_token = malloc(sizeof(t_pre_tokens));
	new_token->next = NULL;
	new_token->content = ft_strdup(data);
	if (!dest)
		dest = new_token;
	else
	{
		temp_dest = dest;
		while (temp_dest->next)
			temp_dest = temp_dest->next;
		temp_dest->next = new_token;
	}
	free(data);
}

void	add_returned_to_files(char *returned, t_command **command_ix, int ret_type)
{
	t_command	*command;

	command = *command_ix;
	/* TYPE_RED_OUT */
	if (ret_type == TYPE_RED_OUT)
		add_pre_t(&(command->output_files), returned);
	/* TYPE_RED_IN */
	if (ret_type == TYPE_RED_IN)
		add_pre_t(&(command->input_files), returned);
	/* TYPE_RED_APP */
	if (ret_type == TYPE_RED_APP)
		add_pre_t(&(command->append_files), returned);
	/* TYPE_RED_HER */
	if (ret_type == TYPE_RED_HER)
		add_pre_t(&(command->herdoc_files), returned);
	free(returned);
}

char	*remove_redirection(t_pre_tokens **args_ix, t_command *command, int *ret_type)
{
	t_pre_tokens	*temp_to_last;
	t_pre_tokens	*tokens_free[2];
	char			*ret_content;
	t_pre_tokens	*args;

	args = *args_ix;
	ret_content = ft_strdup(args->next->next->content);
	*ret_type = args->next->type;
	tokens_free[0] = args->next;
	tokens_free[1] = args->next->next;
	temp_to_last = args->next->next->next;
	args->next = temp_to_last;
	free(tokens_free[0]->content);
	free(tokens_free[1]->content);
	free(tokens_free[0]);
	free(tokens_free[1]);
	return (ret_content);
}


int	check_redirections(t_pre_tokens	**head, t_command **command_ix)
{
	char			*returned;
	t_command 		*command;
	int				ret_type;
	t_pre_tokens	*args;
	int				i = 0;

	command = *command_ix;
	args = *head;
	ret_type = 0;
	while (args->next)
	{
		if (args->next->type != TYPE_ARG)
		{
			if (!(args->next->next))
				return (1);
			else // 
			{
				if (args->next->next->type != TYPE_ARG)
					return (1);
				returned = remove_redirection(&args, command, &ret_type);
				add_returned_to_files(returned, &command, ret_type);
				continue;
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
		command->output_files = NULL;
		command->input_files = NULL;
		command->append_files = NULL;
		command->herdoc_files = NULL;
		ret += check_redirections(&command->args, &command);
		command = command->next;
	}
	if (ret != 0)
	{
		print_error("parsing error\n");
		return (1);
	}
	return (0);
}
