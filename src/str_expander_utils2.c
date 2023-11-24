/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:20:14 by mcarneir          #+#    #+#             */
/*   Updated: 2023/11/22 17:21:04 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

int	if_question_mark(void)
{
	char	*str;
	
	str = ft_itoa(g_status);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": command not found\n", STDOUT_FILENO);
	free(str);
	return (127);
}