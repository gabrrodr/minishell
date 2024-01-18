/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:50:29 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/18 17:06:14 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(t_prompt *prompt, char *val)
{
	int	i[3];

	if (!val)
		return (NULL);
	i[0] = -1;
	while (prompt->env[++i[0]])
	{
		if (!ft_strncmp(val, prompt->env[i[0]], sl(prompt->env[i[0]])))
		{
			free(val);
			i[1] = 0;
			while (prompt->env[i[0]][i[1]] != '=')
				i[1]++;
			val = ft_calloc(ft_strlen(prompt->env[i[0]]) - i[1] + 1,
					sizeof(char));
			if (!val)
				return (NULL);
			i[2] = -1;
			while (prompt->env[i[0]][i[1]])
				val[++i[2]] = prompt->env[i[0]][++i[1]];
			return (val);
		}
	}
	free(val);
	return (NULL);
}

int	ft_is_double_quotes(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

int	env_lines(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**dupe_arr(char **arr)
{
	int		i;
	char	**dupe;

	i = env_lines(arr);
	dupe = ft_calloc(i + 1, sizeof(char *));
	if (!dupe)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		dupe[i] = ft_strdup(arr[i]);
		if (!dupe[i])
		{
			free_array(dupe);
			return (NULL);
		}
		i++;
	}
	return (dupe);
}

void	exit_env(t_prompt *prompt)
{
	printf("exit\n");
	rl_clear_history();
	free_data(prompt, false);
	exit(0);
}
