/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:25:34 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/30 19:01:02 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>

#include <unistd.h>
bool g_was_killed;

static void	handler_sigint_sigquit(int sig)
{
	if (sig == SIGINT)
	{
		g_was_killed = true;
		printf("^C");
		close(STDIN_FILENO);
	}
}

void	sig_here_doc(void)
{
	struct sigaction act;

	rl_catch_signals = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = &handler_sigint_sigquit;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT , &act, NULL);
}
