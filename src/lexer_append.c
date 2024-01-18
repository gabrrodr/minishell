/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:55:45 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/17 18:21:20 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

int	ft_append_separator(t_tokens token, char **line, t_lexer **lexer_tok)
{
	t_lexer	*tok;

	tok = ft_lexernew(NULL, token);
	if (!tok)
		return (0);
	ft_lexeradd_back(lexer_tok, tok);
	*line += 1;
	if (token == LESS_LESS || token == GREAT_GREAT)
		*line += 1;
	return (1);
}

int	ft_append_identifier(char **str, t_lexer **lexer_tok, size_t i)
{
	char	*tmp;
	char	*value;
	t_lexer	*tok;

	tok = NULL;
	tmp = *str;
	while (tmp[i] && !ft_is_separator(tmp + i))
	{
		if (ft_is_quote(tmp[i]))
		{
			if (!ft_skip_quotes(tmp, &i))
				return (ft_print_q_err(tmp[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (0);
	remove_quotes(value);
	tok = ft_lexernew(value, IDENTIFIER);
	if (!tok)
		return (free(value), 0);
	*str += i;
	return (ft_lexeradd_back(lexer_tok, tok), 1);
}
