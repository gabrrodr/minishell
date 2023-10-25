/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:51:42 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/19 17:43:24 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;
	size_t	sizetotal;

	sizetotal = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (sizetotal + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
