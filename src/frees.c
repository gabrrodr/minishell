/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:51:32 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/18 15:52:24 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_prompt	*reset_init(t_prompt *prompt, char **argv, char **env)
{
	char	*path;

	path = NULL;
	prompt->lexer = NULL;
	prompt->simple_cmds = init_simple_cmds();
	prompt->heredoc = malloc(sizeof(t_heredoc));
	if (!prompt->heredoc)
		return (NULL);
	prompt->pid = NULL;
	prompt->exit_codes = NULL;
	init_flags(prompt);
	prompt->env = dupe_arr(env);
	init_vars(prompt, argv, path);
	return (prompt);
}

void	reset_prompt(t_prompt *prompt, char **argv, char **env)
{
	char		**old_env;

	old_env = dupe_arr(prompt->env);
	free_data(prompt, true);
	reset_init(prompt, argv, env);
	prompt->reset = true;
	if (prompt->env)
	{
		free_array(prompt->env);
		prompt->env = old_env;
	}
	else
		free_array(old_env);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_parser(t_simple_cmds *simple_cmds)
{
	t_simple_cmds	*tmp;

	while (simple_cmds)
	{
		if (simple_cmds->str)
			free_array(simple_cmds->str);
		if (simple_cmds->builtin)
			free(simple_cmds->builtin);
		if (simple_cmds->hd_file_name)
		{
			unlink(simple_cmds->hd_file_name);
			free(simple_cmds->hd_file_name);
		}
		if (simple_cmds->redirect)
			free_lexer(simple_cmds->redirect);
		tmp = simple_cmds;
		simple_cmds = simple_cmds->next;
		free (tmp);
	}
	free(simple_cmds);
}

void	free_lexer(t_lexer *lst)
{
	t_lexer	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		if (lst->str)
			free(lst->str);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_data(t_prompt *prompt, bool reset)
{
	if (!prompt)
		return ;
	if (prompt->pid)
		free(prompt->pid);
	if (prompt->lexer)
		free_lexer(prompt->lexer);
	if (prompt->simple_cmds)
		free_parser(prompt->simple_cmds);
	if (prompt->heredoc)
		free(prompt->heredoc);
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->exit_codes)
		free(prompt->exit_codes);
	if (reset)
		prompt = NULL;
	else
	{
		if (prompt->pwd)
			free(prompt->pwd);
		if (prompt->oldpwd)
			free(prompt->oldpwd);
		free(prompt);
	}
}
