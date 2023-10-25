/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:58:54 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/04/20 14:56:40 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dupe;

	i = 0;
	len = ft_strlen(s);
	dupe = malloc(sizeof(char) * (len + 1));
	if (dupe == NULL)
		return (NULL);
	while (s[i])
	{
		dupe[i] = s[i];
		i++;
	}
	dupe[i] = '\0';
	return ((char *)dupe);
}
