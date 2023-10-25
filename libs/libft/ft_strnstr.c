/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:57:03 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/19 17:50:08 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *) big);
	while (big[i] != '\0')
	{
		j = 0;
		while ((big[i + j] == little[j]) && little[j] != '\0' && (i + j < len))
		{
			if (big[i + j] == '\0' && little[j] == '\0')
				return ((char *) &big[i]);
			j++;
		}
		if (little[j] == '\0')
		{
			return ((char *) big + i);
		}
		i++;
	}
	return (0);
}
