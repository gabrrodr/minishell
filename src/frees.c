/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:51:32 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/12/28 16:49:07 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_prompt	*reset_prompt(t_prompt *prompt, char **argv, char **env)
{
	t_prompt	*reset;
	char		**old_env;

	old_env = dupe_arr(prompt->env);
	free_data(prompt);
	reset = init_prompt(argv, env);
	reset->reset = true;
	if (reset->env)
	{
		free_array(reset->env);
		reset->env = old_env;
	}
	else
		free_array(old_env);
	return (reset);
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

void	free_data(t_prompt *prompt)
{
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->simple_cmds)
		free_parser(prompt->simple_cmds);
	if (prompt->lexer)
		free_lexer(prompt->lexer);
	if (prompt->pid)
		free(prompt->pid);
	if (prompt->pwd)
		free(prompt->pwd);
	if (prompt->oldpwd)
		free(prompt->oldpwd);
	if (prompt->exit_codes)
		free(prompt->exit_codes);
	if (prompt->heredoc)
		free(prompt->heredoc);
	free(prompt);
}
