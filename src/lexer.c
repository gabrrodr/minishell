/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:52:05 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/17 16:08:53 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_separator(char **line_ptr, t_lexer **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (ft_append_separator(LESS_LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (ft_append_separator(GREAT_GREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (ft_append_separator(LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (ft_append_separator(GREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "|", 1))
		return (ft_append_separator(PIPE, line_ptr, token_list) && 1);
	else
		return (0);
}

t_lexer	*ft_handle_tokenize(char *str)
{
	t_lexer	*lexer_tok;
	int		error;

	error = 0;
	lexer_tok = NULL;
	while (str && *str)
	{
		if (error)
			return (ft_clear_lexer(&lexer_tok), NULL);
		if (ft_isspace(*str))
		{
			ft_skip_spaces(&str);
		}
		else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1)
			|| !ft_strncmp(str, "|", 1))
			error = (!ft_handle_separator(&str, &lexer_tok) && 1);
		else 
			error = (!ft_append_identifier(&str, &lexer_tok, 0) && 1);
	}
	return (lexer_tok);
}

t_lexer	*lexer(char *input)
{
	t_lexer	*lexer_tok;

	lexer_tok = ft_handle_tokenize(input);
	free(input);
	return (lexer_tok);
}
