/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:03:50 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/25 13:10:06 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_prompt	*prompt;
	char		*input;
	
	if (argc > 1)
	{
		printf("No arguments, please!\n");
		exit(1);
	}
	prompt = init_prompt(argv, env);
	while (prompt)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			free(input);
			exit_env(prompt);
		}
		add_history(input);
	}
}