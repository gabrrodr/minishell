/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:45:27 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:00:53 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**add_single(char **env, char *key)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(key);
	new_env[i + 1] = NULL;
	free_array(env);
	return (new_env);
}

char	**add_env(char **env, char *key, char *value)
{
	char	**new_env;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	tmp = ft_strjoin(key, "=");
	new_env[i] = ft_strjoin(tmp, value);
	free(tmp);
	new_env[i + 1] = NULL;
	free_array(env);
	return (new_env);
}

static void	handle_add_env(t_prompt *prompt, char *cmds)
{
	char	**tmp;

	tmp = ft_split(cmds, '=');
	if (tmp[1])
		prompt->env = add_env(prompt->env, tmp[0], tmp[1]);
	else
		prompt->env = add_env(prompt-> env, tmp[0], "");
	free_array(tmp);
}

int	ms_export(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	**env;
	int		i;

	i = -1;
	env = sort_export(prompt);
	if (!cmds->str[0])
		print_export(env);
	else
	{
		while (cmds->str[++i])
		{
			if (check_params(cmds->str[i]))
				return (EXIT_FAILURE);
			if (check_equal(prompt, cmds, i) == 0)
				handle_add_env(prompt, cmds->str[i]);
			else if (check_equal(prompt, cmds, i) == 1)
				sub_value(prompt, cmds, i);
			else if (check_key(prompt, cmds, i) == 1)
				continue ;
			else
				prompt->env = add_single(prompt->env, cmds->str[i]);
		}
	}
	return (EXIT_SUCCESS);
}
