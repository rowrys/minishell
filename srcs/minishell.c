/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:26:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 22:42:02 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "execute.h"
#include "here_doc.h"
#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "sig.h"
#include "utils.h"

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

extern int	g_was_killed;

static void	ft_manage_line(t_ctx *ctx)
{
	size_t	i;

	ft_split_readline(ctx);
	i = 0;
	while (ctx->line_split[i])
	{
		ctx->line = ft_strdup(ctx->line_split[i]);
		if (!ctx->line)
			ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
		if (*ctx->line)
			add_history(ctx->line);
		if (ft_is_valid_line(ctx, ctx->line))
		{
			ft_parse(ctx);
			if (!ft_here_doc(ctx))
			{
				signal(SIGINT, SIG_IGN);
				ft_execute(ctx);
				signal(SIGINT, &handler_sigint);
			}
		}
		ft_clean_ctx(ctx);
		i++;
	}
	ft_free_double(&ctx->line_split);
}

int	main(int argc, char **argv, char **env)
{
	t_ctx	ctx;

	ft_init_ctx(&ctx, argc, argv, env);
	ft_signal_init();
	while (1)
	{
		ctx.line = readline("minishell$ ");
		if (g_was_killed == SIGINT)
			ctx.last_error = 130;
		if (!ctx.line)
			break ;
		ft_manage_line(&ctx);
		g_was_killed = 0;
	}
	ft_destroy_ctx(&ctx);
	rl_clear_history();
	return (ctx.last_error);
}
