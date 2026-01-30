/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_mini_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:39:09 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/30 18:38:53 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

static void	handler_sigint_sigquit(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	rl_redisplay();
}

void	sig_mini_shell(void)
{
	struct sigaction act;

	rl_catch_signals = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = &handler_sigint_sigquit;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
