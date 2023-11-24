/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:32:31 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/23 17:16:19 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_prompt	*init_vars(t_prompt *prompt, char **argv, char *key)
{
	char	*value;

	key = ms_getenv(prompt->env, "SHLVL=");
	if (!key || ft_atoi(key) <= 0)
	{
		value = ft_strdup("1");
	}
	else
		value = ft_itoa(ft_atoi(key) + 1);
	free(key);
	prompt->env = ms_setenv("SHLVL=", value, prompt->env);
	free(value);
	prompt->env = ms_setenv("PATH=", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt->env);
	key = ms_getenv(prompt->env, "_=");
	if (key)
		prompt->env = ms_setenv("_=", argv[0], prompt->env);
	free(key);
	return (prompt);
}

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
	t_prompt	*prompt;
	char		*path;
	
	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (NULL);
	path = NULL;
	prompt->lexer = NULL;
	prompt->simple_cmds = init_simple_cmds();
	prompt->heredoc = malloc(sizeof(t_heredoc));
	if (!prompt->heredoc)
		return (NULL);
	prompt->heredoc->error_num = 0;
	prompt->interact = false;
	prompt->env = dupe_arr(env);
	prompt = init_vars(prompt, argv, path);
	prompt->flg[0] = 0;
	prompt->flg[1] = 0;
	prompt->flg[2] = 0;
	prompt->pwd = getcwd(NULL, 0);
	prompt->oldpwd = NULL;
	return (prompt);
}
