/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:40:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 13:18:31 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_pwd(t_prompt *prompt)
{
	ft_putendl_fd(prompt->pwd, STDOUT_FILENO);
	return (0);
}

void	ms_echo(t_simple_cmds *process, t_prompt *prompt)
{
	int		i;
	int		j;
	int		n_flag;
	char	**args;

	i = 0;
	n_flag = 0;
	args = process->str;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n') 
	{
		j = 1;
		while (args[i][j] == 'n') 
			j++;
		if (args[i][j] == '\0') 
			n_flag = 1;
		else
			break ;
		i++;
	}
	print_args(prompt, args, i);
	if (!n_flag) 
		printf("\n");
}

int	builtin(t_prompt *prompt, t_simple_cmds *process)
{
	char	*cmd;
	int		status;

	status = 0;
	cmd = process->builtin;
	if (!ft_strncmp(cmd, "pwd", 4))
		ms_pwd(prompt);
	else if (!ft_strncmp(cmd, "echo", 5))
		ms_echo(process, prompt);
	else if (!ft_strncmp(cmd, "export", 7))
		status = ms_export(prompt, process);
	else if (!ft_strncmp(cmd, "unset", 6))
		ms_unset(prompt, process);
	else if (!ft_strncmp(cmd, "env", 4))
		ms_env(prompt);
	else if (!ft_strncmp(cmd, "exit", 5))
		status = ms_exit(prompt, process);
	else if (!ft_strncmp(cmd, "cd", 3))
		status = ms_cd(prompt, process);
	return (status);
}
