/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:36:43 by mcarneir          #+#    #+#             */
/*   Updated: 2024/01/17 18:44:20 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_path(t_prompt *tools)
{
	char	*tmp;

	tmp = ft_strdup(tools->pwd);
	free(tools->oldpwd);
	tools->oldpwd = tmp;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, 0);
}

char	*find_path_ret(char *str, t_prompt *tools)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], str, ft_strlen(str)))
			return (ft_substr(tools->env[i], ft_strlen(str),
					ft_strlen(tools->env[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_prompt *tools, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, tools);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_prompt *tools)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", tools->pwd);
			free(tools->env[i]);
			tools->env[i] = tmp;
		}
		else if (!ft_strncmp(tools->env[i], "OLDPWD=", 7) 
			&& tools->oldpwd)
		{
			tmp = ft_strjoin("OLDPWD=", tools->oldpwd);
			free(tools->env[i]);
			tools->env[i] = tmp;
		}
		i++;
	}
}

int	ms_cd(t_prompt *tools, t_simple_cmds *simple_cmd)
{
	int		ret;

	if (!simple_cmd->str[0] || !ft_strncmp(simple_cmd->str[0], "--", 2) 
		|| !ft_strncmp(simple_cmd->str[0], "~", 1))
		ret = specific_path(tools, "HOME=");
	else if (ft_strncmp(simple_cmd->str[0], "-", 1) == 0)
	{
		ret = specific_path(tools, "OLDPWD=");
		if (ret == 0)
			print_new_directory(tools);
	}
	else if (simple_cmd->str[1] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else
		ret = change_directory(simple_cmd->str[0]);
	if (ret != 0)
		return (1);
	change_path(tools);
	add_path_to_env(tools);
	return (ret);
}
