/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:45:12 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/02 12:51:04 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	size_t	space;
	void	*res;

	space = (nmenb * size);
	res = malloc(space);
	if (!res)
		return (NULL);
	ft_memset(res, 0, space);
	return (res);
}
