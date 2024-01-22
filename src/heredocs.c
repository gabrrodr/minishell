/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:17:23 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:11:27 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

static char	*set_file_name(void)
{
	static int	i = 0;
	char		*file_name;
	char		*tmp;

	tmp = ft_itoa(i);
	file_name = ft_strjoin(".tmp", tmp);
	free(tmp);
	i++;
	return (file_name);
}

static int	heredoc(t_prompt *prompt, t_lexer *redirect, 
	bool quote, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	line = readline("> ");
	while (line && ft_strncmp(line, redirect->str, ft_strlen(redirect->str) + 1)
		&& g_code != 2)
	{
		if (quote == false && !solo_doll_sign(line)
			&& ft_strncmp(line, redirect->str, ft_strlen(redirect->str) + 1))
			line = spicy_expand(prompt, line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (g_code == 2)
		return (1);
	close(fd);
	return (0);
}

static int	check_heredoc(t_prompt *prompt, t_simple_cmds *cmds, 
				t_lexer *redirect, char *file_name)
{
	int		hd;
	bool	quote;

	if ((redirect->str[0] == '\"' && 
			redirect->str[ft_strlen(redirect->str) - 1] == '\"')
		|| (redirect->str[0] == '\'' && 
			redirect->str[ft_strlen(redirect->str) - 1] == '\''))
	{
		quote = true;
	}
	else
		quote = false;
	delquotes(redirect->str, '\"');
	delquotes(redirect->str, '\'');
	hd = heredoc(prompt, redirect, quote, file_name);
	if (cmds && cmds->builtin && ft_strncmp(cmds->builtin, "echo", 5))
	{
		prompt->heredoc->status = true;
	}
	return (hd);
}

int	send_heredoc(t_prompt *prompt, t_simple_cmds *cmds)
{
	t_lexer	*redirect;

	redirect = cmds->redirect;
	while (redirect)
	{
		if (redirect->token == LESS_LESS)
		{
			if (cmds->hd_file_name)
				free(cmds->hd_file_name);
			cmds->hd_file_name = set_file_name();
			if (check_heredoc(prompt, cmds, redirect, cmds->hd_file_name))
			{
				prompt->heredoc->err_num = 1;
				return (1);
			}
		}
		redirect = redirect->next;
	}
	return (0);
}

t_simple_cmds	*single_cmd_heredoc(t_prompt *prompt, t_simple_cmds *cmds)
{
	t_lexer			*redirect;

	(void)prompt;
	redirect = cmds->redirect;
	while (cmds->redirect)
	{
		if (cmds->redirect->next == NULL)
			break ;
		cmds->redirect = cmds->redirect->next;
	}
	cmds->redirect = redirect;
	return (cmds);
}
