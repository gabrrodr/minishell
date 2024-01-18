/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:47:23 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/18 14:55:22 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_var(char *str)
{
	char	*val;
	int		i;
	int		j;
	int		start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '/') 
	{
		if (str[i] == '$' && i > start) 
			break ;
		i++;
	}
	val = ft_calloc(i - start + 1, sizeof(char));
	j = 0;
	while (start < i)
		val[j++] = str[start++];
	return (val);
}

char	*create_str(t_prompt *prompt, char *str, char *var, char *word)
{
	size_t	final_length;
	char	*final_str;

	final_length = (ft_strlen(str) - ft_strlen(word)) + ft_strlen(var);
	final_str = ft_calloc(final_length + 1, sizeof(char));
	if (!final_str)
		return (NULL);
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	while (str[prompt->flg[0]] != '$')
		final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
	ft_strlcat(final_str, var, final_length + 1);
	prompt->flg[0] += ft_strlen(word) + 1;
	while (final_str[prompt->flg[1]])
		prompt->flg[1]++;
	while (str[prompt->flg[0]])
		final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
	return (final_str);
}

static char	*remove_var_from_str(const char *str, const char *word)
{
	char		*result;
	const char	*ptr;
	char		*write_ptr;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
	{
		free (result);
		return (NULL);
	}
	ptr = str;
	write_ptr = result;
	while (*ptr != '\0') 
	{
		if (ft_strstr(ptr, word) == ptr) 
			ptr += ft_strlen(word);
		else 
		{
			*write_ptr = *ptr;
			write_ptr++;
			ptr++;
		}
	}
	*write_ptr = '\0';
	return (result);
}

char	*replace(t_prompt *prompt, char *str)
{
	char	*final_str;
	char	*var;
	char	*word;
	char	*port;

	port = get_var(str);
	word = get_word(str);
	if (!ft_strncmp(word, "?", 2))
		prompt->exit_codes[prompt->flg[2]++] = 1;
	var = get_env(prompt, get_word(str));
	if (!var)
	{
		free(word);
		final_str = remove_var_from_str(str, port);
		free(port);
		return (final_str);
	}
	else
	{
		final_str = create_str(prompt, str, var, word);
		free(word);
		free(var);
		free(port);
		return (final_str);
	}
}

bool	is_only_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
			break ;
	}
	if (!str[i])
		return (true);
	return (false);
}
