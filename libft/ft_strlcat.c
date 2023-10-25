/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:27:34 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/04/20 15:04:03 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(dst);
	i = 0;
	if (size <= j)
		return (ft_strlen(src) + size);
	while (src[i] != '\0' && j + 1 < size)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (j + ft_strlen(&src[i]));
}
/*
int main(void)
{
    char dest[] = "hello bro";
    const char src[] = ", que queres";

    printf("%zu", ft_strlcat(dest, src, 5));
    printf("%zu", ft_strlcat(dest, src, 0));
    printf("%zu", ft_strlcat(dest, src, 15));
    printf("%zu", ft_strlcat(dest, src, 25));
}*/