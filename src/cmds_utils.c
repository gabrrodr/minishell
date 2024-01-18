/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:24:24 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/18 15:04:41 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

int	handle_error_cmd(t_simple_cmds *cmds)
{
	struct stat		st;
	char			*str;
	char			*tmp;
	int				status;

	status = 127;
	if (!cmds->str && !cmds->str[0])
		return (1);
	if (cmds->str[0][0])
		tmp = ft_strdup(cmds->str[0]);
	else
		tmp = ft_strdup("\'\'");
	if ((cmds->str[0][0] == '/' || cmds->str[0][0] == '.')
			&& stat(tmp, &st) == 0 && (S_ISDIR(st.st_mode) | S_IXUSR))
		str = ft_strjoin(tmp, ": Is directory");
	else
		str = ft_strjoin(tmp, ": command not found");
	ft_putendl_fd(str, STDERR_FILENO);
	if ((cmds->str[0][0] == '/' || cmds->str[0][0] == '.')
			&& stat(tmp, &st) == 0 && (S_ISDIR(st.st_mode) | S_IXUSR))
		status = 126;
	free(tmp);
	free(str);
	return (status);
}

int	change_directory(char *path)
{
	int		ret;

	ret = chdir(path);
	if (ret != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		perror(" ");
	}
	return (ret);
}
