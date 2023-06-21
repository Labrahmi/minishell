/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:03:00 by bel-kdio          #+#    #+#             */
/*   Updated: 2023/06/21 15:31:20 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_len_if_sin_quo(int *i, int *len, char *var)
{
	while (var[*i] && var[*i] != '\'')
	{
		(*i)++;
		(*len)++;
	}
	(*i)++;
}

void	get_len_if_db_quo(int *i, int *len, char *var, t_env *env)
{
	char	*key;
	char	*value;

	while (var[*i] != '"')
	{
		if (var[*i] == '$' && ++(*i))
		{
			if (is_valid_variable(var[*i]) == 0)
				(*len)++;
			else
			{
				key = get_index(var + *i);
				if (ft_strncmp(key, "?", 2) == 0)
					value = ft_itoa(glob.exit_status);
				else
					value = get_value(key, &env);
				*i += ft_strlen(key);
				*len += ft_strlen(value);
				free(key);
				free(value);
			}
		}
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	(*i)++;
}

void	get_len_if_db_dollar(int *i, int *len, char *var, t_env *env)
{
	char	*key;
	char	*value;

	if (is_valid_variable(var[*i]) == 0)
		(*len)++;
	else
	{
		key = get_index(var + *i);
		if (ft_strncmp(key, "?", 2) == 0)
			value = ft_itoa(glob.exit_status);
		else
			value = get_value(key, &env);
		*i += ft_strlen(key);
		*len += ft_strlen(value);
		free(key);
		free(value);
	}
}

int	get_len(char *var)
{
	int		len;
	int		i;
	char	*key;
	char	*value;

	len = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '\'' && ++i)
			get_len_if_sin_quo(&i, &len, var);
		else if (var[i] == '"' && ++i)
			get_len_if_db_quo(&i, &len, var, glob.env);
		else if (var[i] == '$' && ++i)
			get_len_if_db_dollar(&i, &len, var, glob.env);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
