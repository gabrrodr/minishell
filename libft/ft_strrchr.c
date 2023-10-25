/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:58:42 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/04/24 15:35:02 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s) + 1;
	while (--i >= 0)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&(s[i]));
		}
	}
	return (NULL);
}
/*
int main()
{
	printf("%s\n", ft_strrchr("skibidi bop", 's'));
}*/