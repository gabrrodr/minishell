/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:42:28 by mcarneir          #+#    #+#             */
/*   Updated: 2023/10/24 16:19:18 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*ft_lexernew(char *str, t_tokens tokenType)
{
	t_lexer *node;
	static int	i;

	i = 0;
	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token = tokenType;
	node->i = i++;
	node->next = NULL;
	node->prev = NULL;
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
