/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:16:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/12 09:50:09 by ykolacze         ###   ########.fr       */
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

static bool	ft_here_doc_cmd(t_ctx *ctx, t_cmd *cmd, bool *here_doc_syntax_error)
{
	t_list	*token_list;
	t_token	*token;
	bool	was_killed;
	size_t	i;

	token_list = cmd->token;
	was_killed = false;
	while (token_list && !was_killed)
	{
		token = token_list->content;
		if (token->type == KEY_HERE_DOC)
		{
			if (token->value)
				i = ft_skip(token->value, ISSPACE);
			if (!token->value || !token->value[i])
			{
				*here_doc_syntax_error = true;
				return (was_killed);
			}
			was_killed = ft_here_doc_token(ctx, cmd, token->value);
		}
		token_list = token_list->next;
	}
	return (was_killed);
}

static bool	ft_manage_here_doc(t_ctx *ctx, bool *is_syntax_error)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	bool	was_killed;
	bool	here_doc_syntax_error;

	was_killed = false;
	here_doc_syntax_error = false;
	cmd_list = ctx->cmd_lst;
	while (cmd_list && !was_killed)
	{
		cmd = cmd_list->content;
		was_killed = ft_here_doc_cmd(ctx, cmd, &here_doc_syntax_error);
		if (!was_killed && here_doc_syntax_error)
		{
			if (*is_syntax_error == false)
			{
				*is_syntax_error = true;
				ft_putendl_fd(SYNTAX_HERE_DOC, 2);
				ctx->last_error = 2;
			}
			return (was_killed);
		}
		cmd_list = cmd_list->next;
	}
	return (was_killed);
}

static bool	ft_check_syntax_error_pipe(t_ctx *ctx)
{
	if (ft_is_syntax_error_pipe(ctx->line))
	{
		ft_putendl_fd(SYNTAX_PIPE, 2);
		ctx->last_error = 2;
		return (true);
	}
	return (0);
}

bool	ft_here_doc(t_ctx *ctx)
{
	bool	is_syntax_error;
	bool	killed;

	is_syntax_error = false;
	killed = false;
	is_syntax_error = ft_check_syntax_error_pipe(ctx);
	killed = ft_manage_here_doc(ctx, &is_syntax_error);
	if (killed)
	{
		ctx->last_error = 130;
		return (true);
	}
	if (!is_syntax_error && ft_is_syntax_error_redir(ctx->line))
	{
		ft_putendl_fd(SYNTAX_REDIR, 2);
		ctx->last_error = 2;
		is_syntax_error = true;
	}
	return (is_syntax_error);
}
