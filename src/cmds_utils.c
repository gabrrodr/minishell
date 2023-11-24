/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:24:24 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/24 16:34:28 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

int	handle_error_cmd(t_simple_cmds *cmds)
{
	char	*tmp;

	if (!cmds->str && !cmds->str[0])
		return (1);
	if (cmds->str[0][0])
		tmp = ft_strdup(cmds->str[0]);
	else
		tmp = ft_strdup("\'\'");
	ft_strjoin(tmp, ": command not found");
	ft_putendl_fd(tmp, STDERR_FILENO);
	free(tmp);
	return (127);
}