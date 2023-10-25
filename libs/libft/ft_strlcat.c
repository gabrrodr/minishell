/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:17:38 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/19 17:38:31 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	i = 0;
	sl = ft_strlen(src);
	dl = ft_strlen(dst);
	if (!src && !dst)
		return (0);
	if (size == 0)
		return (ft_strlen((char *)src));
	if (dl >= size)
		return (size + sl);
	while (src[i] != '\0' && i < size - dl - 1)
	{
		dst[dl + i] = src[i];
		i++;
	}
	if (src[0] != '\0')
		dst[dl + i] = '\0';
	return (dl + sl);
}
