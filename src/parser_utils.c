/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:47:16 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/02 12:53:43 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(char **str)
{
	if (!str)
		return (1);
	if ((str[0] == "<" || str[0] == ">") && ft_strlen(str) == 1)
		return (0);
	if ((ft_strncmp(str, "<<", 2) || ft_strncmp(str, ">>", 2)) && ft_strlen(str) == 2)
		return (0);
	return (1);
}