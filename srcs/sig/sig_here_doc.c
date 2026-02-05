/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:25:34 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/05 19:10:35 by mcolin           ###   ########.fr       */
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
	signal(SIGINT, &handler_sigint_sigquit);
	signal(SIGQUIT, &handler_sigint_sigquit);
}
