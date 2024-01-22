/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expandable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:30:27 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/18 18:36:26 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	handle_dol(char *str, int i, bool in_single_quotes)
{
	if (str[i] == '$' && in_single_quotes)
		return (false);
	else if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes)
		return (true);
	else if (str[i] == '$' && !in_single_quotes)
	{
		if (!ft_isdigit(str[i + 1]))
		{
			if (solo_doll_sign(str))
			{
				return (false);
			}
			else
				return (true);
		}
		else 
			return (false);
	}
	else if (str[i] == '$' && ft_isdigit(str[i + 1]) && !in_single_quotes)
		return (false);
	return (true);
}

bool	is_expandable(char *str)
{
	bool	in_double_quotes;
	bool	in_single_quotes;
	int		i;

	in_double_quotes = false;
	in_single_quotes = false;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
			&& !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
			&& !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (str[i] == '$')
			return (handle_dol(str, i, in_single_quotes));
		else if (((str[i] == '<' && str[i + 1] == '<') 
				|| (str[i] == '>' && str[i + 1] == '>')) 
			&& there_is_expand(str, i))
			return (false);
	}
	return (true);
}
