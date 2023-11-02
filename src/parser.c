/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:10:10 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/02 17:18:56 by mcarneir         ###   ########.fr       */
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

void	process_tokens(t_prompt *prompt, t_simple_cmds *cmds)
{
	int		size;
	
	size = nbr_nodes(prompt->lexer);
	if (!cmds->str)
	{
		cmds->str = malloc(sizeof(char *) * (size + 1));
		if (!cmds->str)
			return ;
		cmds->str[size] = NULL;
	}
	while (prompt->lexer)
	{
		if (prompt->lexer->token == IDENTIFIER)
		{
			if (prompt->flag == 0 && is_builtin(prompt->lexer->str))
				cmds->builtin = ft_strdup(prompt->lexer->str);
			else if (is_redirection(prompt->lexer->str))
				break ;
			else
				cmds->str[prompt->flag] = ft_strdup(prompt->lexer->str);
			prompt->flag++;	
		}
		prompt->lexer = prompt->lexer->next;
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
			prompt->flag = 0;
			cmds_tmp = init_simple_cmds();
			if (!cmds_tmp)
				return ;
			cmds->next = cmds_tmp;
			cmds_tmp->prev = cmds;
			cmds = cmds->next;
		}
		redirections(prompt, cmds);
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
		if (lexer->token && !ft_strncmp(lexer->token, "|", 1))
			pipes++;
		lexer = lexer->next;
	}
	prompt->simple_cmds = init_simple_cmds();
	get_simple_cmds(prompt, pipes);
	if (!prompt->simple_cmds)
		return ;
}