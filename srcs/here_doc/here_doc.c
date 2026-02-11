/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:16:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/11 20:34:32 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "sig.h"
#include "utils.h"

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

#define SYNTAX_PIPE "minishell: syntax error near unexpected token 'pipe'"
#define SYNTAX_REDIR "minishell: syntax error near unexpected token 'redir'"
#define SYNTAX_HERE_DOC "minishell: syntax error near unexpected token '<<'"

extern int	g_was_killed;

static bool	ft_here_doc_token(t_ctx *ctx, t_cmd *cmd, char *block)
{
	char	*limiter;
	bool	do_expand;
	bool	was_killed;

	do_expand = true;
	ft_close(&cmd->pipe_hd[0]);
	if (pipe(cmd->pipe_hd) == -1)
		ft_error(ctx, "pipe: ", EXIT_FAILURE);
	limiter = ft_get_limiter(ctx, block, &do_expand);
	g_was_killed = 0;
	signal(SIGINT, &handler_sigint_here_doc);
	was_killed = ft_get_here_doc(ctx, limiter, do_expand, cmd->pipe_hd[1]);
	signal(SIGINT, &handler_sigint);
	free(limiter);
	ft_close(&cmd->pipe_hd[1]);
	return (was_killed);
}

static bool	ft_here_doc_cmd(t_ctx *ctx, t_cmd *cmd)
{
	t_list	*token_list;
	t_token	*token;
	bool	was_killed;

	token_list = cmd->token;
	was_killed = false;
	while (token_list && !was_killed)
	{
		token = token_list->content;
		if (token->type == KEY_HERE_DOC)
			was_killed = ft_here_doc_token(ctx, cmd, token->value);
		token_list = token_list->next;
	}
	return (was_killed);
}

static bool	ft_manage_here_doc(t_ctx *ctx)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	bool	was_killed;

	was_killed = false;
	cmd_list = ctx->cmd_lst;
	while (cmd_list && !was_killed)
	{
		cmd = cmd_list->content;
		was_killed = ft_here_doc_cmd(ctx, cmd);
		cmd_list = cmd_list->next;
	}
	return (was_killed);
}

static bool	ft_check_syntax_error(t_ctx *ctx)
{
	if (ft_is_syntax_error_pipe(ctx->line))
	{
		ft_putendl_fd(SYNTAX_PIPE, 2);
		ctx->last_error = 2;
		return (true);
	}
	if (ft_is_syntax_error_redir_here_doc(ctx->line))
	{
		ft_putendl_fd(SYNTAX_HERE_DOC, 2);
		ctx->last_error = 2;
		return (true);
	}
	return (false);
}

bool	ft_here_doc(t_ctx *ctx)
{
	bool	is_syntax_error;
	bool	killed;

	is_syntax_error = false;
	killed = false;
	if (ft_check_syntax_error(ctx))
		is_syntax_error = true;
	killed = ft_manage_here_doc(ctx);
	if (killed)
		ctx->last_error = 130;
	if (!killed && ft_is_syntax_error_redir(ctx->line))
	{
		ft_putendl_fd(SYNTAX_REDIR, 2);
		ctx->last_error = 2;
		is_syntax_error = true;
	}
	return (is_syntax_error | killed);
}
