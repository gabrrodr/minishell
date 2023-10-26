/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:03:50 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/10/26 16:14:51 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		input = readline("\033[95mminishell$ \033[0m");
		if (input == NULL || !ft_strcmp(input, "exit"))
		{
			free(input);
			exit_env(prompt);
		}
		add_history(input);
		prompt->lexer = lexer(input);
		for (t_lexer *node = prompt->lexer; node; node = node->next)
		{
			if (!node->str)
				printf("[%d] ", node->token);
			else
				printf("[%s] ", node->str);
		}
		printf("\n");
	}
	exit_env(prompt);
}