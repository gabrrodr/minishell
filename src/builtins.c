/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:40:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/13 11:34:01 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s", pwd);
	free(pwd);
}

void	ms_echo(char **args) 
{
    int	i;

	i = 0;
	if (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		i++;
		while (args[i]) 
		{
        	printf("%s", args[i]);
        	if (args[i + 1]) 
			{
            	printf(" ");
			}
			i++;
    	}
	} 
	else
	{
        while (args[i]) 
		{
        	printf("%s", args[i]);
        	if (args[i + 1])
			{
        		printf(" ");
			}
			i++;
		}
		printf("\n");
	}
}

int	builtin(t_prompt *prompt, t_simple_cmds *process)
{
	char	*cmd;

	cmd = process->builtin;

	if (!ft_strncmp(cmd, "pwd", 3))
		ms_pwd();
	else if (!ft_strncmp(cmd, "echo", 4))
		ms_echo(prompt->simple_cmds->str);
	else if (!ft_strncmp(cmd, "export", 6))
		ms_export(prompt, process);
	else if (!ft_strncmp(cmd, "unset", 5))
		ms_unset(prompt, process);
	else if (!ft_strncmp(cmd, "env", 3))
		ms_env(prompt);
	//else if (!ft_strncmp(cmd, "exit", 4))
	//	ms_exit(prompt, process);
	//else if (!ft_strncmp(cmd, "cd", 2))
	//	ms_cd(prompt, process);
	return (0);
}