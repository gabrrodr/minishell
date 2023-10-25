/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:26:09 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/04/26 11:44:51 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char delim)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == delim)
			i++;
		if (s[i])
			count += 1;
		while (s[i] && s[i] != delim)
			i++;
	}
	return (count);
}

static size_t	size_specific_word(char *s, char delim)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != delim)
		i += 1;
	return (i);
}

static char	*words(char *s, char delim)
{
	size_t	i;
	size_t	len;
	char	*word;

	len = size_specific_word(s, delim);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i += 1;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	j;

	if (!s)
	{
		return (NULL);
	}
	res = malloc((count_words(s, c) + 1) * sizeof(char *));
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
			j += 1;
		}
		while (*s && *s != c)
			s++;
	}
	res[j] = 0;
	return (res);
}

/*
int main(void)
{
	char **res;
	size_t i = 0;
	res = ft_split("eu sou eu sou", ' ');
	while (i < count_words("eu sou eu sou", ' '))
	{
		printf("%s\n", res[i]);
		i += 1;
	}
}
*/