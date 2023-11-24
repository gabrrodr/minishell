/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:32:31 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/23 15:08:50 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_pid(t_prompt *prompt)
{
	t_simple_cmds	*process;
	int				n_processes;

	process = prompt->simple_cmds;
	n_processes = 0;
	while(process)
	{
		n_processes++;
		process = process->next;
	}
	prompt->pid = malloc(sizeof(int) * n_processes);
	if (!prompt->pid)
		return (ms_error(1));
	return (0);
}

t_simple_cmds	*init_simple_cmds(void)
{
	t_simple_cmds	*cmds;

	cmds = malloc(sizeof(t_simple_cmds));
	if (!cmds)
		return (NULL);
	cmds->str = NULL;
	cmds->builtin = NULL;
	cmds->num_redirections = 0;
	cmds->hd_file_name = NULL;
	cmds->redirect = NULL;
	cmds->next = NULL;
	cmds->prev = NULL;
	return (cmds);
}

t_prompt	*init_prompt(char **argv, char **env)
{
	(void)argv;
	t_prompt	*prompt;
	
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->lexer = NULL;
	prompt->simple_cmds = init_simple_cmds();
	prompt->heredoc = malloc(sizeof(t_heredoc));
	if(!prompt->heredoc)
		return (NULL);
	prompt->heredoc->err_num = 0;
	prompt->heredoc->status = false;
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	prompt->flg[2] = 0;
	prompt->reset = false;
	prompt->pid = NULL;
	prompt->env = dupe_arr(env);
	prompt->pwd = getcwd(NULL, 0);
	prompt->oldpwd = NULL;
	prompt->exit_codes = NULL;
	return (prompt);
}
