/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:13:40 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/27 23:13:44 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pre_tokens	*add_to_command(t_pre_tokens *node, t_command **f_command)
{
	t_command		*new_command;
	t_command		*last_command;
	t_pre_tokens	*temp_node;
	t_pre_tokens	*ret_node;
	t_pre_tokens	*temp_free;

	// - - - - - - - -
	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return 0;
	// - - - - - - - -
	temp_node = node;
	new_command->f_arg = node;
	new_command->next = NULL;
	// - - - - - - - -
	while (temp_node->next && (ft_strncmp(temp_node->next->content, "|", ft_strlen(temp_node->next->content)) != 0))
		temp_node = temp_node->next;
	// - - - - - - - -
	ret_node = temp_node->next;
	if (temp_node)
		temp_node->next = 0;
	// - - - - - - - -
	if (!(*f_command))
		*f_command = new_command;
	else
	{
		last_command = *f_command;
		while (last_command->next)
			last_command = last_command->next;
		last_command->next = new_command;
	}
	return (ret_node);
}

t_command	*ft_fill_commands(t_pre_tokens **head)
{
	t_command		*f_command;
	t_pre_tokens	*node;
	t_pre_tokens	*temp_next;

	if (!head || !(*head))
		return (0);
	f_command = 0;
	node = *head;
	while (node && (ft_strncmp(node->content, "|", ft_strlen(node->content)) == 0))
		node = node->next;
	while (node)
	{
		temp_next = add_to_command(node, &f_command);
		node = temp_next;
		while (node && (ft_strncmp(node->content, "|", ft_strlen(node->content)) == 0))
		{
			t_pre_tokens	*_temp_to_next;
			_temp_to_next = node->next;
			free(node);
			free(node->content);
			node = _temp_to_next;
		}
	}
	return (f_command);
}
