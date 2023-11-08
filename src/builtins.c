/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:40:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/07 11:45:44 by gabrrodr         ###   ########.fr       */
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