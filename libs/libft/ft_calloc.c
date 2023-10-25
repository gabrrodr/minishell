/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:45:12 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/20 15:03:59 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmenb, size_t size)
{
	size_t	space;
	void	*res;

	space = (nmenb * size);
	res = malloc(space);
	if (res == 0)
		return (NULL);
	ft_memset(res, 0, space);
	return (res);
}
