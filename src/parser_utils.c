/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:47:16 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/12/28 12:45:07 by mcarneir         ###   ########.fr       */
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
	if (!ft_strncmp(str, "echo", 5) || !ft_strncmp(str, "cd", 3) 
		|| !ft_strncmp(str, "pwd", 4) || !ft_strncmp(str, "export", 7)
		|| !ft_strncmp(str, "unset", 6) || !ft_strncmp(str, "env", 4)
		|| !ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

int	nbr_nodes(t_lexer *lexer)
{
	int		i;
	t_lexer	*tmp;

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

void	alloc_double_array(int size, t_simple_cmds *cmds)
{
	cmds->str = ft_calloc(size + 1, sizeof(char *));
	if (!cmds->str)
		return ;
	cmds->str[size] = NULL;
}
