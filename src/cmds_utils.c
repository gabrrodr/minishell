/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:24:24 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/15 12:39:06 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

int handle_error_cmd(t_simple_cmds *cmds)
{
    struct stat    st;
    char      *str;
    char      *tmp;
    int          status;

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
