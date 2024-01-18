/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:32:31 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/18 15:56:00 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_pid(t_prompt *prompt)
{
	t_simple_cmds	*process;
	int				n_processes;

	process = prompt->simple_cmds;
	n_processes = 0;
	while (process)
	{
		n_processes++;
		process = process->next;
	}
	if (!n_processes)
		return (1);
	prompt->pid = ft_calloc(n_processes, sizeof(int));
	if (!prompt->pid)
		return (ms_error(1));
	return (0);
}

void	init_vars(t_prompt *prompt, char **argv, char *key)
{
	char	*value;
	char	*path;

	path = "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin";
	key = ms_getenv(prompt->env, "SHLVL=");
	if (!key || ft_atoi(key) <= 0)
	{
		value = ft_strdup("1");
	}
	else
		value = ft_itoa(ft_atoi(key) + 1);
	free(key);
	prompt->env = ms_setenv("SHLVL=", value, prompt->env);
	free (value);
	key = ms_getenv(prompt->env, "PATH=");
	if (!key)
		prompt->env = ms_setenv("PATH=", path, prompt->env);
	free(key);
	key = ms_getenv(prompt->env, "_=");
	if (key)
		prompt->env = ms_setenv("_=", argv[0], prompt->env);
	free(key);
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

void	init_flags(t_prompt *prompt)
{
	prompt->heredoc->err_num = 0;
	prompt->heredoc->status = false;
	prompt->interact = false;
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	prompt->flg[2] = 0;
	prompt->flg[3] = 0;
	prompt->reset = false;
}

t_prompt	*init_prompt(char **argv, char **env)
{
	t_prompt	*prompt;
	char		*path;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	path = NULL;
	prompt->lexer = NULL;
	prompt->heredoc = malloc(sizeof(t_heredoc));
	if (!prompt->heredoc)
		return (NULL);
	prompt->simple_cmds = init_simple_cmds();
	init_flags(prompt);
	prompt->pid = NULL;
	prompt->env = dupe_arr(env);
	prompt->pwd = getcwd(NULL, 0);
	init_vars(prompt, argv, path);
	prompt->oldpwd = NULL;
	prompt->exit_codes = NULL;
	return (prompt);
}
