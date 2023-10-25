/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:10:47 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/20 15:18:58 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen((char *)s) + 1;
	while (--l >= 0)
	{
		if (s[l] == (unsigned char)c)
		{
			return ((char *)&(s[l]));
		}
	}
	return (NULL);
}
