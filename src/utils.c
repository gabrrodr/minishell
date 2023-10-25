/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:50:29 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/25 13:52:53 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dupe_arr(t_prompt *prompt)
{
	
}

void	exit_env(t_prompt *prompt)
{
	printf("exit\n");
	free_data(prompt);
}