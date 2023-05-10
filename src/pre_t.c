/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:01:42 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/10 15:36:14 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void add_to_last(t_pre_tokens **head, t_pre_tokens *next_node)
{
	t_pre_tokens	*node;

	if (*head)
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = next_node;
	}
	else
		*head = next_node;
}

int add_pre_t(t_pre_tokens **head, char *content)
{
	t_pre_tokens *create_new_node;

	if (!(content) || ft_strlen(content) == 0)
		return(0);
	if(!(create_new_node = malloc(sizeof(t_pre_tokens))))
		return(0);
	create_new_node->content = ft_strdup(content);
	create_new_node->next = NULL;
	add_to_last(head, create_new_node);
	return(1);
}
