/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:38:54 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/22 12:58:15 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

static void	print_exit_status(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		write(STDOUT_FILENO, &str[i++], 1);
	tmp = ft_itoa(g_code);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	free(tmp);
	i += 2;
	while (str[i])
		write(STDOUT_FILENO, &str[i++], 1);
}

void	print_args(t_prompt *prompt, char **args, int i)
{
	while (args[i]) 
	{
		if (is_exit_status(args[i]))
		{
			if (prompt->exit_codes[current_exit_status(prompt)] == 1)
				print_exit_status(args[i]);
			else
				ft_putstr_fd(args[i], STDOUT_FILENO);
			prompt->exit_codes[current_exit_status(prompt)] = 2;
		}
		else
			ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

void	print_new_directory(t_prompt *tools)
{
	char	*oldpwd;

	oldpwd = find_path_ret("OLDPWD=", tools);
	if (oldpwd)
	{
		ft_putendl_fd(oldpwd, STDOUT_FILENO);
		free(oldpwd);
	}
}
