/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:29:07 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/24 14:01:58 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*replace;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	replace = ft_lstlast(*lst);
	replace->next = new;
}
