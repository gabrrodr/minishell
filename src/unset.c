/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:05:56 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:11:56 by gabrrodr         ###   ########.fr       */
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

static int	handle_unset_errors(char *str)
{
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	unset_errors(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || ft_isdigit(str[0]) || ft_strchr(str, '='))
	{
		handle_unset_errors(str);
		return (EXIT_FAILURE);
	}
	while (str[i])
	{
		if (is_identifier(str[i]))
		{
			handle_unset_errors(str);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_var(t_prompt *prompt, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prompt->env[i])
	{
		if (!ft_strncmp(prompt->env[i], str, ft_strlen(str)))
			return (0);
		else
			j = 0;
		i++;
	}
	return (1);
}

int	ms_unset(t_prompt *prompt, t_simple_cmds *cmds)
{
	char	**tmp;
	int		i;

	i = -1;
	if (!cmds->str[0])
	{
		return (EXIT_FAILURE);
	}
	else
	{
		while (cmds->str[++i])
		{
			if (unset_errors(cmds->str[i]))
				break ;
			if (!check_var(prompt, cmds->str[i]))
			{
				tmp = ft_unsetenv(prompt->env, cmds->str[i]);
				free_array(prompt->env);
				prompt->env = tmp;
			}
		}
	}
	return (EXIT_SUCCESS);
}
