/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:42:28 by mcarneir          #+#    #+#             */
/*   Updated: 2023/12/28 12:39:35 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*ms_lstlast(t_lexer *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_lexer	*ft_lexernew(char *str, t_tokens tokenType)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token = tokenType;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_lexeradd_back(t_lexer **lst, t_lexer *node)
{
	t_lexer	*tmp;

	tmp = *lst;
	if (!node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp; 
}

void	ft_clear_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*tmp2;

	tmp = *lexer;
	if (!tmp)
		return ;
	while (tmp)
	{
		free(tmp->str);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*lexer = NULL;
}
