/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expander_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:20:14 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/18 14:55:06 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

int	if_question_mark(void)
{
	char	*str;

	str = ft_itoa(g_code);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free(str);
	return (127);
}

static char	*get_exit(char *str, int *i)
{
	char	*val;
	int		j;
	int		start;

	j = 0;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '\"' 
		&& str[*i] != '/' && !ft_isalnum(str[*i]))
	{
		if (str[*i] == '$' && *i > start)
			break ;
		(*i)++;
	}
	val = ft_calloc(*i - start + 1, sizeof(char));
	while (start < *i)
		val[j++] = str[start++];
	return (val);
}

char	*create_str_2(t_prompt *prompt, char *str, char *var, char *word)
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
	{
		final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
	}
	prompt->flg[0]--;
	ft_strlcat(final_str, var, final_length + 1);
	prompt->flg[0] += ft_strlen(word) + 1;
	while (final_str[prompt->flg[1]])
		prompt->flg[1]++;
	while (str[prompt->flg[0]])
		final_str[prompt->flg[1]++] = str[prompt->flg[0]++];
	return (final_str);
}

char	*replace_exit_mark(t_prompt *prompt, char **str, int *j, int *len)
{
	char	*word;
	char	*exit;
	char	*final_str;

	word = get_exit(*str, j);
	exit = ft_itoa(g_code);
	final_str = create_str_2(prompt, *str, exit, word);
	if (final_str)
	{
		free(*str);
		*str = ft_strdup(final_str);
		free(final_str);
		*j = -1;
		*len = ft_strlen(*str);
	}
	free(word);
	free(exit);
	return (*str);
}
