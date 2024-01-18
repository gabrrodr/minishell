/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:18:52 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/18 18:37:28 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	there_is_expand(char *str, int i)
{
	int	j;

	j = i;
	while (str[j])
	{
		if (str[j] == '$')
			return (true);
		j++;
	}
	return (false);
}
