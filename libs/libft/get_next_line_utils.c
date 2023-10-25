/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:08:27 by mcarneir          #+#    #+#             */
/*   Updated: 2023/06/27 18:50:32 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!stash)
	{
		stash = (char *)malloc(sizeof(char));
		stash[0] = '\0';
	}
	dest = (char *)malloc(sizeof(char) * ((ft_strlen_gnl(stash)
					+ ft_strlen_gnl(buffer)) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		dest[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		dest[i++] = buffer[j++];
	dest[i] = '\0';
	free(stash);
	return (dest);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[ft_strlen_gnl(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_clean_stash(char *stash)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n' && stash[i] != '\r')
		i++;
	if (!stash[i] || stash[i] == '\r')
	{
		free(stash);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (stash[i++])
		str[j++] = stash[i];
	str[j] = '\0';
	free(stash);
	cleanup_str(&str);
	return (str);
}

void	cleanup_str(char **str)
{
	if ((*str)[0] == '\0')
	{
		free (*str);
		*str = 0;
	}
}
