/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:18:52 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/19 13:12:02 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	there_is_expand(char *str, int i)
{
	int	j;

	j = i;
	while (str[j])
	{
		if (str[j] == '$')
			return (true);
		j++;
	}
	return (false);
}

bool	doll_between_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '$' && str[i + 2] == '\'')
			|| (str[i] == '\"' && str[i + 1] == '$' && str[i + 2] == '\"'))
			return (true);
		i++;
	}
	return (false);
}

int	sl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

t_prompt	*reset_init(t_prompt *prompt, char **argv, char **env)
{
	char	*path;

	path = NULL;
	prompt->lexer = NULL;
	prompt->simple_cmds = init_simple_cmds();
	prompt->heredoc = malloc(sizeof(t_heredoc));
	if (!prompt->heredoc)
		return (NULL);
	prompt->pid = NULL;
	prompt->exit_codes = NULL;
	init_flags(prompt);
	prompt->env = dupe_arr(env);
	init_vars(prompt, argv, path);
	return (prompt);
}
