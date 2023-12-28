/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:05:56 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/12/28 13:12:54 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_unsetenv(char **env, char *name)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

static int	unset_errors(t_simple_cmds *cmds)
{
	int	i;

	i = 0;
	if (!cmds->str[0])
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (cmds->str[0][i])
	{
		if (ft_isdigit(cmds->str[0][0]) 
			|| (!ft_isalnum(cmds->str[0][i]) && cmds->str[0][i] != '_'))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(cmds->str[0], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_unset(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	**tmp;

	if (unset_errors(cmds) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else
	{
		tmp = ft_unsetenv(prompt->env, cmds->str[0]);
		free_array(prompt->env);
		prompt->env = tmp;
	}
	return (EXIT_SUCCESS);
}
