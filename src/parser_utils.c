/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:47:16 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/02 17:47:18 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(t_tokens tokenType)
{
	if (tokenType == LESS || tokenType == LESS_LESS
		|| tokenType == GREAT || tokenType == GREAT_GREAT)
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2) 
		|| !ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "export", 6)
		|| !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "env", 3)
		|| !ft_strncmp(str, "exit", 4))
		return (1);
	return (0);
}

int	nbr_nodes(t_lexer *lexer)
{
	int		i;
	t_lexer *tmp;

	i = 0;
	tmp = lexer;
	while (tmp && (tmp->str || tmp->token))
	{
		if (tmp->token && tmp->token == PIPE)
			return (i);
		if (tmp->token && tmp->token != IDENTIFIER)
		{
			if (tmp->next && (tmp->next->next || tmp->next->token))
				tmp = tmp->next->next;
			else
				tmp = tmp->next;
		}
		else if (is_builtin(tmp->str))
			tmp = tmp->next;
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}