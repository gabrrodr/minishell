/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:50:29 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/03 12:53:45 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_lines(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	dupe_arr(t_prompt *prompt, char **arr)
{
	int		i;
	char	**dupe;

	i = env_lines(arr);
	dupe = ft_calloc(i + 1, sizeof(char *));
	if (!dupe)
		return ;
	i = 0;
	while (arr[i])
	{
		dupe[i] = ft_strdup(arr[i]);
		if (!dupe[i])
		{
			free_array(dupe);
			return ;
		}
		i++;
	}
	prompt->env = dupe;
}

void	exit_env(t_prompt *prompt)
{
	printf("exit\n");
	free_data(prompt);
	exit(0);
}
