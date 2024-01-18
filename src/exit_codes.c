/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:56:29 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/17 18:22:43 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_exit_status(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			if (str[i + 1] && str[i + 1] == '?')
				return (true);
	}
	return (false);
}

int	current_exit_status(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (prompt->exit_codes[i] == 2)
		i++;
	return (i);
}
