/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:49:33 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/28 01:14:33 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int main(int argc, char const *argv[])
{
	int	fd = open("out.txt", O_CREAT | O_RDONLY | O_WRONLY, 777);
	dup2(fd, STDOUT_FILENO);
	printf("Hello World 1\n");
	close(fd);
	return 0;
}
