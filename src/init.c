/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:32:31 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/16 14:01:55 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_simple_cmds	*init_simple_cmds(void)
{
	t_simple_cmds	*cmds;

	cmds = malloc(sizeof(t_simple_cmds));
	if (!cmds)
		return (NULL);
	cmds->str = NULL;
	cmds->builtin = NULL;
	cmds->num_redirections = 0;
	cmds->hd_file_name = NULL;
	cmds->redirect = NULL;
	cmds->next = NULL;
	cmds->prev = NULL;
	return (cmds);
}

t_prompt	*init_prompt(char **argv, char **env)
{
	(void)argv;
	t_prompt	*prompt;
	
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	prompt->lexer = NULL;
	prompt->simple_cmds = init_simple_cmds();
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	prompt->flg[2] = 0;
	prompt->env = dupe_arr(env);
	prompt->pwd = getcwd(NULL, 0);
	prompt->oldpwd = NULL;
	return (prompt);
}
