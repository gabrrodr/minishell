/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:10:10 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:10:40 by gabrrodr         ###   ########.fr       */
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
			cmds->redirect = ft_lexernew(NULL, prompt->lexer->token);
		else
			ft_lexeradd_back(&cmds->redirect, 
				ft_lexernew(NULL, prompt->lexer->token));
		prompt->lexer = prompt->lexer->next;
		if (prompt->lexer && prompt->lexer->str)
		{
			tmp = ms_lstlast(cmds->redirect);
			tmp->str = ft_strdup(prompt->lexer->str);
			prompt->lexer = prompt->lexer->next;
		}
	}
}

void	process_tokens(t_prompt *prompt, t_simple_cmds *cmds)
{
	int		size;

	size = nbr_nodes(prompt->lexer);
	if (!cmds->str)
		alloc_double_array(size, cmds);
	while (prompt->lexer)
	{
		if (is_redirection(prompt->lexer->token))
			return ;
		if (prompt->lexer->token == IDENTIFIER)
		{
			if (prompt->flg[3] == 0 && is_builtin(prompt->lexer->str)
				&& !cmds->builtin)
				cmds->builtin = ft_strdup(prompt->lexer->str);
			else
			{
				cmds->str[prompt->flg[3]] = ft_strdup(prompt->lexer->str);
				prompt->flg[3]++;
			}
		}
		if (prompt->lexer && prompt->lexer->token == PIPE)
			return ;
		prompt->lexer = prompt->lexer->next;
	}
}

void	get_simple_cmds(t_prompt *prompt, int pipes)
{
	t_lexer			*lexer_tmp;
	t_simple_cmds	*cmds;
	t_simple_cmds	*cmds_tmp;

	lexer_tmp = prompt->lexer;
	cmds = prompt->simple_cmds;
	while (prompt->lexer && pipes >= 0)
	{
		if (prompt->lexer->token && prompt->lexer->token == PIPE)
		{
			prompt->lexer = prompt->lexer->next;
			pipes--;
			prompt->flg[3] = 0;
			cmds_tmp = init_simple_cmds();
			cmds->next = cmds_tmp;
			cmds_tmp->prev = cmds;
			cmds = cmds->next;
		}
		redirections(prompt, cmds);
		if (prompt->lexer && prompt->lexer->token == PIPE)
			continue ;
		process_tokens(prompt, cmds);
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
		if (lexer->token && lexer->token == PIPE)
			pipes++;
		lexer = lexer->next;
	}
	prompt->flg[3] = 0;
	get_simple_cmds(prompt, pipes);
	if (!prompt->simple_cmds)
		return ;
}
