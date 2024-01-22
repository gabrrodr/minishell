/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:34:24 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:39:41 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*move_to_next_node(t_lexer *tmp)
{
	if (tmp->next && (tmp->next->next || tmp->next->token))
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	return (tmp);
}
