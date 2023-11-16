/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:54:20 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/13 17:28:12 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_env(t_prompt *prompt)
{
	int		i;

	i = 0;
	while (prompt->env[i])
	{
		if (ft_strchr(prompt->env[i], '='))
		{
			ft_putstr_fd(prompt->env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
}
