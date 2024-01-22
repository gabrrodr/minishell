/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:04:13 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/19 11:20:58 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

int	error_redirections(t_lexer *lexer)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (lexer && lexer->token == GREAT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (lexer && lexer->token == GREAT_GREAT)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (lexer && lexer->token == LESS)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (lexer && lexer->token == LESS_LESS)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (lexer && lexer->token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("'newline'\n", STDERR_FILENO);
	return (1);
}

int	check_redirections(t_prompt *prompt)
{
	t_lexer	*tmp;

	tmp = prompt->lexer;
	while (tmp)
	{
		if (tmp->token == GREAT || tmp->token == GREAT_GREAT
			|| tmp->token == LESS || tmp->token == LESS_LESS)
		{
			if ((tmp->next && tmp->next->token != IDENTIFIER) || !tmp->next)
			{
				g_code = 2;
				return (error_redirections(tmp));
			}
		}
		else if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE 
				|| !tmp->prev))
		{
			g_code = 2;
			return (error_redirections(tmp));
		}
		tmp = tmp->next;
	}
	return (0);
}

/*int	check_redirections(t_prompt *prompt)
{
	t_lexer	*tmp;

	tmp = prompt->lexer;
	while (tmp)
	{
		if (tmp->token == GREAT || tmp->token == GREAT_GREAT
			|| tmp->token == LESS || tmp->token == LESS_LESS
			|| tmp->token == PIPE)
		{
			tmp = tmp->next;
			if (!tmp || tmp->token != IDENTIFIER)
			{
				g_code = 2;
				return (error_redirections(tmp));
			}
			if (tmp->str && !ft_strncmp(tmp->str, "$", 1))
			{
				g_code = 1;
				ft_putstr_fd("bash: ", STDERR_FILENO);
				ft_putstr_fd(tmp->str, STDERR_FILENO);
				ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}*/
