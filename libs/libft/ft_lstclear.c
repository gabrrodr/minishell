/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:41:24 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/24 14:01:34 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*replace;

	if (!lst)
		return ;
	while (*lst)
	{
		replace = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = replace;
	}
	*lst = NULL;
}
