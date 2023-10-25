/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:44:08 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/04/24 16:32:13 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//s is the string from which you create the substring
//start is the index of the substring in s
//len is the maximum lenght of the substring

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)malloc((len + 1) * sizeof (*s));
	if (!sub)
		return (NULL);
	while (i < ft_strlen(s) && j < len)
	{
		sub[j] = s[i];
		j++;
		i++;
	}
	sub[j] = '\0';
	return (sub);
}
/*
#include<stdio.h>

int main(void)
{
    char const *str = "hi hello my name is alberto";
    unsigned int    i = 9;
    
    printf("%s", ft_substr(str, i, 19));
}*/