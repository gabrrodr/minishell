/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:54:20 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/04 12:14:54 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_env(t_prompt *prompt)
{
	int		i;

	i = 0;
	while (prompt->env[i])
	{
		if (ft_strchr(prompt->env[i], '='))
		{
			ft_putstr_fd(prompt->env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
}

char	*ms_getenv(char **env, char *var)
{
	int		i;

	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
			return (ft_substr(env[i], ft_strlen(var) + 1,
					ft_strlen(env[i])));
	}
	return (NULL);
}

char	**extend_env(char **env, char *new)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i + 2);
	if (!new_env)
		return (env);
	j = 0;
	while (i < j)
	{
		new_env[j] = ft_strdup(env[j]);
		if (!new_env[j])
			free_array(env);
		j++;
	}
	new_env[j] = ft_strdup(new);
	return (new_env);
}

char	**ms_setenv(char *variable, char *value, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(variable, value);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], variable, ft_strlen(variable)) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(tmp);
			free(tmp);
			return (env);
		}
		i++;
	}
	env = extend_env(env, tmp);
	free(tmp);
	return (env);
}
