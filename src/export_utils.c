/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:28:47 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/12/28 16:30:40 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_export(t_prompt *prompt)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (prompt->env[i])
	{
		j = i + 1;
		while (prompt->env[j])
		{
			if (ft_strcmp(prompt->env[i], prompt->env[j]) > 0)
			{
				tmp = prompt->env[i];
				prompt->env[i] = prompt->env[j];
				prompt->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (prompt->env);
}

int	check_variable(t_prompt *prompt, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new[j] != '=' && new[j])
		j++;
	while (prompt->env[i])
	{
		if (ft_strncmp(prompt->env[i], new, j) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_equal(t_prompt *prompt, t_simple_cmds *cmds, int i)
{
	if (ft_strchr(cmds->str[i], '='))
	{
		if (!check_variable(prompt, cmds->str[i]))
			return (0);
		else if (check_variable(prompt, cmds->str[i]))
			return (1);
	}
	return (2);
}

int	check_key(t_prompt *prompt, t_simple_cmds *cmds, int i)
{
	int		j;

	j = 0;
	while (prompt->env[j])
	{
		if (ft_strncmp(prompt->env[j], cmds->str[i], 
				ft_strlen(cmds->str[i])) == 0)
			return (1);
		else
			j++;
	}
	return (0);
}

void	sub_value(t_prompt *prompt, t_simple_cmds *cmds, int i)
{
	char	**tmp;
	int		k;

	tmp = ft_split(cmds->str[i], '=');
	k = 0;
	while (prompt->env[k])
	{
		if (tmp[0] && 
			ft_strncmp(prompt->env[k], cmds->str[i], ft_strlen(tmp[0])) == 0)
		{
			free(prompt->env[k]);
			prompt->env[k] = ft_strdup(cmds->str[i]);
			free_array(tmp);
			break ;
		}
		else
			k++;
	}
}
