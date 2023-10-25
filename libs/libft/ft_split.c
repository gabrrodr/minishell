/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:51:27 by mcarneir          #+#    #+#             */
/*   Updated: 2023/04/21 18:35:56 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char delim)

{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == delim)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != delim)
			i++;
	}
	return (count);
}

static size_t	size_specific_word(char *s, char delim)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != delim)
	{
		i++;
	}
	return (i);
}

static char	*words(char *s, char delim)
{
	size_t	i;
	size_t	len;
	char	*word;

	len = size_specific_word(s, delim);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	j;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			res[j] = words((char *)s, c);
			j++;
		}
		while (*s && *s != c)
			s++;
	}
	res[j] = 0;
	return (res);
}
