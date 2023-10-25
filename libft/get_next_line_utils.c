/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:30:26 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/07/03 16:51:26 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *stash, char *buffer)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!stash)
	{
		stash = (char *)malloc(sizeof(char) * 1);
		stash[0] = '\0';
	}
	dst = (char *)malloc(sizeof(char) * (ft_strlen(stash) 
				+ ft_strlen(buffer) + 1));
	if (!dst)
		return (NULL);
	while (stash[i])
	{
		dst[i] = stash[i];
		i++;
	}
	while (buffer[j])
		dst[i++] = buffer[j++];
	dst[ft_strlen(stash) + ft_strlen(buffer)] = '\0';
	free(stash);
	return (dst);
}

char	*check_emptystr(char *str)
{
	if (str[0] == '\0')
	{
		free(str);
		str = 0;
	}
	return (str);
}

char	*clean(char *stash)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen(stash) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		str[j++] = stash[i++];
	str[j] = '\0';
	free(stash);
	str = check_emptystr(str);
	return (str);
}
