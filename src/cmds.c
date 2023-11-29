/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:09:48 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/29 13:10:09 by gabrrodr         ###   ########.fr       */
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
	if (cmds->redirect)
	{
		if (setup_redirect(cmds))
			exit (1);
	}
	if (cmds->builtin)
	{
		g_code = builtin(prompt, cmds);
		prompt->heredoc->err_num += g_code;
		exit(g_code);
	}
	else if (cmds->str[0])
		g_code = system_cmd(prompt, cmds);
	exit(g_code);
}

int	single_cmd(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	*cmd;
	int		pid;
	int		status;

	status = 0;
	cmd = cmds->builtin;
	prompt->simple_cmds = single_cmd_heredoc(prompt, cmds);
	if (cmd && (!ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "cd", 2)
			|| !ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5)))
	{
		prompt->heredoc->err_num += builtin(prompt, prompt->simple_cmds);
		g_code = prompt->heredoc->err_num;
		return (0);
	}
	send_heredoc(prompt, prompt->simple_cmds);
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
