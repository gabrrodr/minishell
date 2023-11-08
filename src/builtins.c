/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:07:02 by mcarneir          #+#    #+#             */
/*   Updated: 2023/11/06 18:02:06 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s", pwd);
	free(pwd);
}

void	ms_echo(char **args) 
{
    int	i;

	i = 0;
	if (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		i++;
		while (args[i]) 
		{
        	printf("%s", args[i]);
        	if (args[i + 1]) 
			{
            	printf(" ");
			}
			i++;
    	}
	} 
	else
	{
        while (args[i]) 
		{
        	printf("%s", args[i]);
        	if (args[i + 1])
			{
        		printf(" ");
			}
			i++;
		}
		printf("\n");
	}
}
