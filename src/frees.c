/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:51:32 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/25 13:53:02 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_parser(t_simple_cmds *simple_cmds)
{
	if (simple_cmds->str)
		free_array(simple_cmds->str);
	if (simple_cmds->builtin)
		free_array(simple_cmds->builtin);
	if (simple_cmds->num_redirections)
		free(simple_cmds->num_redirections);
	if (simple_cmds->hd_file_name)
		free_array(simple_cmds->hd_file_name);
}

void	free_data(t_prompt *prompt)
{
	if (prompt->env)
		free_array(prompt->env);
	if (prompt->simple_cmds);
		free_parser(prompt->simple_cmds);
	rl_clear_history();
	free (prompt);
}