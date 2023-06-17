/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:06 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/06/17 16:09:56 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *error_msg, int error_num)
{
	if (!error_msg)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_msg, 2);
	glob.exit_status = error_num;
}
