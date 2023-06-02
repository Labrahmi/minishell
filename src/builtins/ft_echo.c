/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:22:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/06/02 17:39:38 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_zeros(int *ret, int *is_n, int *inv_flag)
{
	*ret = 0;
	*is_n = 0;
	*inv_flag = 0;
}

void	print_new_line(int inv_flag, int is_n)
{
	if (inv_flag)
	{
		printf("\n");
		return ;
	}
	if (!is_n)
		printf("\n");
}

void	print_args(t_pre_tokens *args)
{
	while (args)
	{
		printf("%s", args->content);
		args = args->next;
		if (args)
			printf(" ");
	}
}

int	ft_echo(t_pre_tokens **args_head)
{
	int				ret;
	int				i;
	int				is_n;
	int				inv_flag;
	t_pre_tokens	*args;

	set_zeros(&ret, &is_n, &inv_flag);
	args = *args_head;
	while (args && args->content[0] == '-')
	{
		i = 0;
		while (args->content[++i])
		{
			if (args->content[i] == 'n')
				is_n = 1;
			else
				inv_flag = 1;
		}
		args = args->next;
	}
	if (inv_flag)
		args = *args_head;
	print_args(args);
	print_new_line(inv_flag, is_n);
	return (ret);
}
