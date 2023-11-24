/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:09:48 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/24 14:34:22 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

char	**get_path(t_prompt *prompt)
{
	char	**paths;
	char	*tmp_path;
	char	*path;
	int		i;

	i = -1;
	path = ms_getenv(prompt->env, "PATH");
	paths = ft_split(path, ':');
	free(path);
	while (paths[++i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = tmp_path;
	}
	return (paths);
}

int	system_cmd(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	*sub_path;
	char	**path;
	int		i;
	
	if (!access(cmds->str[0], F_OK))
		execve(cmds->str[0], cmds->str, prompt->env);
	path = get_path(prompt);
	i = -1;
	while (path[++i])
	{
		sub_path = ft_strjoin(path[i], cmds->str[0]);
		if (!access(sub_path, F_OK))
			execve(sub_path, cmds->str, prompt->env);
		free(sub_path);
	}
	free_array(path);
	return (handle_error_cmd(cmds));
}

int	handle_cmd(t_prompt *prompt, t_simple_cmds *cmds)
{
	int		status;

	status = 0;
	if (cmds->builtin)
	{
		status = builtin(prompt, cmds);
		prompt->heredoc->error_num += status;
		exit(status);
	}
	else if (cmds->str[0])
		status = system_cmd(prompt, cmds);
	g_code = status;
	exit(status);
}

int	single_cmd(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	*cmd;
	int		pid;
	int		status;

	status = 0;
	cmd = cmds->builtin;
	
	if (cmd && (!ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "cd", 2)
			|| !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5)))
	{
		prompt->heredoc->error_num += builtin(prompt, prompt->simple_cmds);
		g_code = 0;
		return (0);
	}
	pid = fork();
	if (pid < 0)
		ms_error(5);
	if (pid == 0)
	{
		handle_cmd(prompt, prompt->simple_cmds);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_code = WEXITSTATUS(status);
	return (0);
}

int	cmds(t_prompt *prompt)
{
	t_simple_cmds	*cmds;

	cmds = prompt->simple_cmds;
	if (!cmds->next)
		return (single_cmd(prompt, cmds));
	return (0);
}