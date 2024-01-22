/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:09:48 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 12:20:36 by gabrrodr         ###   ########.fr       */
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
	if (!path)
		return (NULL);
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
	if (!path)
		return (handle_error_cmd(cmds));
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

void	free_exit(t_prompt *prompt)
{
	free_data(prompt, false);
	exit(1);
}

int	handle_cmd(t_prompt *prompt, t_simple_cmds *cmds)
{
	if (cmds->redirect)
	{
		if (setup_redirect(cmds))
			free_exit(prompt);
	}
	if (cmds->builtin)
	{
		g_code = builtin(prompt, cmds);
		free_data(prompt, false);
		exit(g_code);
	}
	else if (!ft_strncmp(cmds->str[0], "$?", 3))
	{
		if (prompt->exit_codes[current_exit_status(prompt)] == 1)
			g_code = if_question_mark();
		else
			g_code = system_cmd(prompt, cmds);
		prompt->exit_codes[current_exit_status(prompt)] = 2;
	}
	else if (cmds->str[0])
		g_code = system_cmd(prompt, cmds);
	free_data(prompt, false);
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
	if (cmd && (!ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "cd", 3)
			|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)))
	{
		g_code = builtin(prompt, prompt->simple_cmds);
		return (0);
	}
	send_heredoc(prompt, prompt->simple_cmds);
	pid = fork();
	if (pid < 0)
		ms_error(5);
	if (pid == 0)
		handle_cmd(prompt, prompt->simple_cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_code = WEXITSTATUS(status);
	return (0);
}
