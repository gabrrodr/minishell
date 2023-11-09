/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:40:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/09 12:29:42 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin(t_prompt *prompt, t_simple_cmds *process)
{
	char	*cmd;

	cmd = process->builtin;

	if (!ft_strncmp(cmd, "pwd", 3))
		ms_pwd();
	else if (!ft_strncmp(cmd, "echo", 4))
		ms_echo(prompt->simple_cmds->str);
	else if (!ft_strncmp(cmd, "cd", 2))
		ms_cd(prompt, process);
	return (0);
}

void	ms_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
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

int	ms_cd(t_prompt *prompts, t_simple_cmds *cmds)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;

	path = cmds->str[1];
	if (!path)
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	oldpwd = ft_strdup(prompts->env[ft_getenv(prompts->env, "OLDPWD")]);
	ft_setenv(prompts->env, "OLDPWD", oldpwd);
	ft_setenv(prompts->env, "PWD", pwd);
	free(pwd);
	free(oldpwd);
	return (0);
}


