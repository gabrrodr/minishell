/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:03:50 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/11/02 18:06:19 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	dev_mod1(t_prompt *prompt)
{
	for (t_lexer *node = prompt->lexer; node; node = node->next)
	{
		if (!node->str)
			printf("[%u] ", node->token);
		else
			printf("[%s] ", node->str);
	}
}

static void	dev_mod2(t_prompt *prompt)
{
	t_simple_cmds	*cmds;
	t_lexer			*node;
	int				j;
	int				i;

	printf("\n\n\n\033[1;32m* PARSER *\033[0m");
	printf("\n\033[1;32m--------------------------------------\033[0m\n");
	cmds = prompt->simple_cmds;
	j = 0;
	while (cmds)
	{
		printf("\nPROCESS[%d]:\n", ++j);
		printf("\n  \033[0;34mSTR:\033[0m ");
		i = -1;
		while (cmds->str && cmds->str[++i])
			printf("[%s] ", cmds->str[i]);
		printf("\n  \033[0;34mBUILTIN:\033[0m %s\n", cmds->builtin);
		printf("  \033[0;34mREDIRCT NUMBER:\033[0m %d\n", cmds->num_redirections);
		printf("  \033[0;34mREDIRCT:\033[0m ");
		node = cmds->redirect;
		while (node)
		{
			if (node->token)
				printf("[%u]", node->token);
			if (node->str)
				printf("[%s]", node->str);
			printf("  ");
			node = node->next;
		}
		printf("\n");
		cmds = cmds->next;
	}
}

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
		dev_mod1(prompt);
		parser(prompt);
		dev_mod2(prompt);
	}
	exit_env(prompt);
}