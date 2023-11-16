/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:40:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/16 14:05:08 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(t_prompt *prompt, t_simple_cmds *process)
{
	char	*cmd;

	cmd = process->builtin;

	if (!ft_strncmp(cmd, "pwd", 4))
		ms_pwd(prompt);
	else if (!ft_strncmp(cmd, "echo", 5))
		ms_echo(prompt->simple_cmds->str);
	else if (!ft_strncmp(cmd, "cd", 3))
		ms_cd(prompt, process);
	else if (!ft_strncmp(cmd, "env", 4))
		ms_env(prompt);
	return (0);
}

int	ms_pwd(t_prompt *prompt)
{
	ft_putendl_fd(prompt->pwd, STDOUT_FILENO);
	return (0);
}

void	ms_echo(char **args)
{
    int i;
	int j;
    int n_flag;

	i = 0;
	n_flag = 0;
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n') 
	{
        j = 1;
        while (args[i][j] == 'n') 
            j++;
        if (args[i][j] == '\0') 
            n_flag = 1;
		else 
            break;
        i++;
    }
    print_args(args, i);
    if (!n_flag) 
        printf("\n");
}



