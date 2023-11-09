/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:38:54 by mcarneir          #+#    #+#             */
/*   Updated: 2023/11/08 16:39:50 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_args(char **args, int i)
{
	while (args[i]) 
	{
        printf("%s", args[i]);
        if (args[i + 1])
        	printf(" ");
        i++;
    }
}