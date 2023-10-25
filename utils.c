/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:50:29 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/25 13:18:41 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dupe_arr(t_prompt *prompt)
{
	
}

void	exit_env(t_prompt *prompt)
{
	printf("exit\n");
	free_data(prompt);
}