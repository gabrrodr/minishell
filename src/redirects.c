/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:02:28 by mcarneir          #+#    #+#             */
/*   Updated: 2023/12/28 12:50:38 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_outfile(t_lexer *redirect)
{
	int	fd_out;

	if (redirect->token == GREAT)
		fd_out = open(redirect->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(redirect->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
		return (ms_error(6));
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		return (ms_error(4));
	close(fd_out);
	return (0);
}

static int	handle_infile(char *str)
{
	int	fd_in;

	fd_in = open(str, O_RDONLY);
	if (fd_in < 0)
		return (ms_error(7));
	if (fd_in > 0 && dup2(fd_in, STDIN_FILENO) < 0)
		return (ms_error(4));
	if (fd_in > 0)
		close(fd_in);
	return (0);
}

int	setup_redirect(t_simple_cmds *cmd)
{
	t_lexer	*redirect;

	redirect = cmd->redirect;
	while (redirect)
	{
		if (redirect->token == LESS)
		{
			if (handle_infile(redirect->str))
				return (1);
		}
		else if (redirect->token == LESS_LESS)
		{
			if (handle_infile(cmd->hd_file_name))
				return (1);
		}
		else if (redirect->token == GREAT 
			|| redirect->token == GREAT_GREAT)
		{
			if (handle_outfile(redirect))
				return (1);
		}
		redirect = redirect->next;
	}
	return (0);
}
