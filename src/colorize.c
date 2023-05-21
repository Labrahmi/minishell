/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:52:43 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/05/15 15:12:05 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_color(char *message, char *color_tag)
{
	char *prefix;

	prefix = ft_strdup(color_tag);
	char *colored_message = ft_strjoin(prefix, message);
	free(prefix);
	prefix = colored_message;
	prefix = ft_strjoin(prefix, "\033[0m");
	free(colored_message);
	return (prefix);
}

char	*ft_colorize(char *message, char *color)
{
	if (ft_strncmp(color, "green", 6) == 0)
		return (ft_get_color(message, "\033[1;32m"));
	if (ft_strncmp(color, "red", 4) == 0)
		return (ft_get_color(message, "\033[31m"));
	else
		return (ft_strdup(message));
}

