/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:48:24 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 09:12:47 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int	g_was_killed;

void	handler_sigint(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handler_sigint_here_doc(int sig)
{
	g_was_killed = sig;
	write(1, "^C", 2);
	close(STDIN_FILENO);
}

void	ft_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_signal_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}
