/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:58:13 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/16 15:45:44 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_digit(char **word, int *j, int *len)
{
	int	k;

	k = *j + 2;
	if (k >= *len || (*word)[k] == '\0') 
	{
		(*word)[*j] = '\0';
		*len = *j;
		*j = -1;
		return ;
	}
	while ((*word)[k] != '\0') 
	{
		(*word)[*j] = (*word)[k];
		(*j)++;
		k++;
	}
	(*word)[*j] = '\0';
	*len = *j;
	*j = -1;
}

static void	handle_expandable(t_prompt *prompt, char **word, int *j, int *len)
{
	char	*tmp;

	tmp = replace(prompt, *word);
	if (tmp)
	{
		free(*word);
		*word = ft_strdup(tmp);
		free(tmp);
		*j = -1;
		*len = ft_strlen(*word);
	}
}
static void	expand_word(t_prompt *prompt, char **word)
{
	int		j;
	int		len;

	j = -1;
	len = ft_strlen(*word);
	while (++j < len)
	{
		if ((*word)[j] == '$' && is_expandable(*word) && !solo_doll_sign(*word) && !is_exit_status(*word))
			handle_expandable(prompt, word, &j, &len);
		else if (!is_expandable(*word) && (*word)[j] == '$' 
				&& ft_isdigit((*word)[j + 1]))
			handle_digit(word, &j, &len);
	}
	if (is_expandable(*word) && is_exit_status(*word))
		prompt->exit_codes[prompt->flg[2]++] = 1;
}

char	*expand_input(t_prompt *prompt, char *input)
{
	prompt->flg[2] = 0;
	init_exit_codes(prompt, input);
	if (!prompt->exit_codes)
		return (NULL);
	expand_word(prompt, &input);
	return (input);
}

