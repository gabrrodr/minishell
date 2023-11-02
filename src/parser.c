/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:10:10 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/02 13:13:17 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirections(t_prompt *prompt, t_simple_cmds *cmds)
{
	t_lexer	*tmp;

	if (prompt->lexer && is_redirection(prompt->lexer->token))
	{
		cmds->num_redirections++;
		if (!cmds->redirect)
			cmds->redirect = ft_lexernew(prompt->lexer->token, NULL, 't');
		else
			ft_lexeradd_back(cmds->redirect, ft_lexernew(prompt->lexer->token, NULL, 't'));
		prompt->lexer = prompt->lexer->next;
		if (prompt->lexer && prompt->lexer->str)
		{
			tmp = ms_lstlast(cmds->redirect);
			tmp->next = ft_strdup(prompt->lexer->str);
			prompt->lexer = prompt->lexer->next;
		}
	}
}

void	get_simple_cmds(t_prompt *prompt, int pipes)
{
	t_lexer	*lexer_tmp;
	t_simple_cmds	*cmds;
	t_simple_cmds	*cmds_tmp;
	
	lexer_tmp = prompt->lexer;
	cmds = prompt->simple_cmds;
	while (prompt->lexer && pipes >= 0)
	{
		if (prompt->lexer->token && !ft_strncmp(prompt->lexer->token, "|", 1))
		{
			lexer_tmp = prompt->lexer->next;
			pipes--;
			cmds_tmp = init_simple_cmds();
			if (!cmds_tmp)
				return ;
			cmds->next = cmds_tmp;
			cmds_tmp->prev = cmds;
			cmds = cmds->next;
		}
		redirections(prompt, cmds);
		
	}
	prompt->lexer = lexer_tmp;
}

void	parser(t_prompt *prompt)
{
	int		pipes;
	t_lexer	*lexer;

	pipes = 0;
	lexer = prompt->lexer;
	while (lexer)
	{
		if (lexer->token && !ft_strncmp(lexer->token, "|", 1))
			pipes++;
		lexer = lexer->next;
	}
	get_simple_cmds(prompt, pipes);
	if (!prompt->simple_cmds)
		return ;
}