/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:44:25 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/22 14:25:08 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

static int	dup_process(t_prompt *prompt, t_simple_cmds *cmd, 
	int fd_in, int end[2])
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		return (1);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		return (1);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(prompt, cmd);
	return (0);
}

static int	check_fd_heredoc(t_prompt *prompt, t_simple_cmds *cmd, int end[2])
{
	int	fd_in;

	if (prompt->heredoc->status)
	{
		close(end[0]);
		if (!cmd->hd_file_name)
			return (-1);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
		if (fd_in == -1)
			return (-1);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

static int	ft_fork(t_prompt *prompt, t_simple_cmds *cmd, int fd_in, int end[2])
{
	static int	i;

	if (!i)
		i = 0;
	if (prompt->reset == true)
	{
		i = 0;
		prompt->reset = false;
	}
	prompt->pid[i] = fork();
	if (prompt->pid[i] < 0)
		return (ms_error(5));
	if (prompt->pid[i] == 0)
	{
		if (dup_process(prompt, cmd, fd_in, end))
			return (ms_error(4));
	}
	i++;
	return (0);
}

static void	pipewait(t_prompt *prompt, int *pid)
{
	t_simple_cmds	*process;
	int				i;
	int				status;
	int				n_pipes;

	n_pipes = 0;
	process = prompt->simple_cmds;
	while (process)
	{
		n_pipes++;
		process = process->next;
	}
	i = -1;
	while (++i < n_pipes - 1)
		waitpid(pid[i], &status, 0);
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
	{
		prompt->heredoc->status = WEXITSTATUS(status);
		g_code = WEXITSTATUS(status);
	}
}

int	execute(t_prompt *prompt)
{
	t_simple_cmds	*cmd;
	int				fd_in;
	int				end[2];

	fd_in = STDIN_FILENO;
	cmd = prompt->simple_cmds;
	if (!cmd->next)
		return (single_cmd(prompt, cmd));
	while (cmd)
	{
		if (cmd->next)
			pipe(end);
		if (send_heredoc(prompt, cmd))
			return (1);
		if (ft_fork(prompt, cmd, fd_in, end))
			return (1);
		close(end[1]);
		if (cmd->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(prompt, cmd, end);
		cmd = cmd->next;
	}
	pipewait(prompt, prompt->pid);
	return (0);
}
