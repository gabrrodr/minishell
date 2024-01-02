/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:45:14 by gabrrodr          #+#    #+#             */
/*   Updated: 2023/12/28 12:51:00 by mcarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_code;

void	execute_signal(int sig, void *prompt)
{
	static t_prompt	*static_prompt;

	if (!static_prompt && prompt)
		static_prompt = (t_prompt *)prompt;
	if (static_prompt && static_prompt->interact)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			printf("\b\b  \b\b");
			rl_redisplay();
		}
	}
	if (!(static_prompt->interact))
		if (sig == SIGINT)
			write(1, &"\n", 1);
	if (sig == SIGINT)
		g_code = 130;
}

static void	handle_signal(int sig)
{
	execute_signal(sig, 0);
}

void	set_sign(void)
{
	struct sigaction	lol;

	lol.sa_handler = &handle_signal;
	lol.sa_flags = 0;
	sigemptyset(&lol.sa_mask);
	sigaction(SIGINT, &lol, NULL);
	sigaction(SIGQUIT, &lol, NULL);
}
