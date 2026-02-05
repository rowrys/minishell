/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_mini_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:39:09 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/05 19:09:57 by mcolin           ###   ########.fr       */
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
	rl_catch_signals = 0;

	signal(SIGINT, &handler_sigint_sigquit);
	signal(SIGQUIT, &handler_sigint_sigquit);
}
