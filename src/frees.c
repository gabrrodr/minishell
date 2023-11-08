/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:51:32 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/06 11:55:40 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	
	if (!simple_cmds)
		return ;
	while (simple_cmds)
	{
		if (simple_cmds->str)
			free_array(simple_cmds->str);
		if (simple_cmds->builtin)
			free(simple_cmds->builtin);
		if (simple_cmds->hd_file_name)
			free(simple_cmds->hd_file_name);
		if (simple_cmds->redirect)
			free_lexer(simple_cmds->redirect);
		tmp = simple_cmds;
		simple_cmds = simple_cmds->next;
		free(tmp);
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
	if (!prompt)
		return ;
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->simple_cmds)
		free_parser(prompt->simple_cmds);
	if (prompt->lexer)
		free_lexer(prompt->lexer);
	free(prompt);
}

t_prompt	*reset_prompt(t_prompt *prompt, char **argv, char **env)
{	
	t_prompt	*reset;
	
	free_data(prompt);
	reset = init_prompt(argv, env);

	return (reset);
}
