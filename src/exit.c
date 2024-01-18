/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:23:10 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/18 15:47:13 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_code(char **str)
{
	int	exit_code;

	if (!str[0])
		exit_code = 0;
	else if (str[0][0] == '#')
		exit_code = g_code;
	else if (is_digit(str[0]))
		exit_code = ft_atoi(str[0]);
	else if (str[0][0] == '-' && is_digit(str[0] + 1))
		exit_code = 256 - ft_atoi(str[0] + 1);
	else if (str[0][0] == '+' && is_digit(str[0] + 1))
		exit_code = ft_atoi(str[0] + 1);
	else
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(str[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 2;
	}
	free_array(str);
	exit(exit_code);
}

int	ms_exit(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	**str;

	if (!cmds)
	{
		free_data(prompt, false);
		exit(g_code);
	}
	if (!cmds->prev)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmds->str[0] && cmds->str[1])
	{
		if (is_digit(cmds->str[0]))
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			g_code = 1;
			return (g_code);
		}
	}
	str = dupe_arr(cmds->str);
	free_data(prompt, false);
	rl_clear_history();
	exit_code(str);
	return (EXIT_SUCCESS);
}
