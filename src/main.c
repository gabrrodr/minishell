/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrrodr <gabrrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:03:50 by gabrrodr          #+#    #+#             */
/*   Updated: 2024/01/22 16:10:06 by gabrrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_code;

/*static void dev_mod(t_prompt *prompt)
{
   t_simple_cmds  *cmds;
   t_lexer          *node;
   int             j;
   int             i;

   printf("\n\033[1;32m* LEXER *\033[0m");
   printf("\n\033[1;32m--------------------------------------\033[0m\n");
   for (t_lexer *node = prompt->lexer; node; node = node->next)
   {
      if (!node->str)
         printf("[%u] ", node->token);
      else
         printf("[%s] ", node->str);
   }
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
   printf("\n\033[1;32m* OUTPUT *\033[0m");
   printf("\n\033[1;32m--------------------------------------\033[0m\n");
   //exit(1);
}*/

/*static void	end_program(char *input, t_prompt *prompt)
{
	free(input);
	free_data(prompt);
	rl_clear_history();
}*/

static t_prompt	*start_program(int argc, char **argv, char **env)
{
	t_prompt	*prompt;

	if (argc > 1)
	{
		ft_printf("No arguments, please!\n");
		exit(1);
	}
	prompt = init_prompt(argv, env);
	set_sign();
	execute_signal(0, prompt);
	return (prompt);
}

static char	*handle_input(t_prompt *prompt, char *input)
{
	if (input == NULL)
	{
		free(input);
		printf("exit\n");
		ms_exit(prompt, NULL);
	}
	if (input[0] && !is_only_whitespaces(input))
		add_history(input);
	if (input || input[0])
		input = expand_input(prompt, input);
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	*prompt;
	char		*input;

	prompt = start_program(argc, argv, env);
	while (prompt)
	{
		prompt->interact = true;
		input = readline("\001\e[1;35m\002minishell$ \001\e[0m\002");
		prompt->interact = false;
		input = handle_input(prompt, input);
		prompt->lexer = lexer(input);
		if (!prompt->lexer)
		{
			reset_prompt(prompt, argv, env);
			continue ;
		}
		if (prompt->lexer && !check_redirections(prompt))
		{
			parser(prompt);
			if (prompt->simple_cmds && !init_pid(prompt))
				execute(prompt);
		}
		reset_prompt(prompt, argv, env);
	}
}
