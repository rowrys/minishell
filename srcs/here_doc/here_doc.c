/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:16:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/30 19:55:10 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"
#include "here_doc.h"
#include "sig.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdatomic.h>
#include <stdbool.h>

extern bool g_was_killed;

static bool	ft_get_here_doc(t_ctx *ctx, char *limiter, bool do_expand, int fd)
{
	char	*line;
	bool	was_killed;
	int		total_size_write;
	int		tmp_stdin;

	total_size_write = 0;
	was_killed = false;
	tmp_stdin = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_was_killed)
		{
			g_was_killed = false;
			dup2(tmp_stdin, STDIN_FILENO);
			return (true);
		}
		// ft_checkdouble
		if (ft_check_limiter(line, limiter, &total_size_write))
			return (was_killed);
		if (do_expand)
			line = ft_manage_expand(ctx, line, 0);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (was_killed);
}

static bool	ft_here_doc_token(t_ctx *ctx, t_cmd *cmd, char *block)
{
	char	*limiter;
	bool	do_expand;
	bool	was_killed;

	do_expand = true;
	// 
	pipe(cmd->pipe_hd);
	// if (pipe(&cmd->pipe_hd) == -1)
	// 	ft_error (pipe);
	limiter = ft_get_limiter(ctx, block, &do_expand);
	g_was_killed = false;
	sig_here_doc();
	was_killed = ft_get_here_doc(ctx, limiter, do_expand, cmd->pipe_hd[1]);
	sig_mini_shell();
	free(limiter);
	ft_close(&cmd->pipe_hd[1]);
	ft_replace_fd(&cmd->fd_in, cmd->pipe_hd[0]);
	return (was_killed);
}

static bool	ft_here_doc_cmd(t_ctx *ctx, t_cmd *cmd)
{
	t_list	*token_list;
	t_token	*token;
	bool	was_killed;

	token_list = cmd->token;
	was_killed = false;
	while (token_list)
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
	while (cmd_list)
	{
		cmd = cmd_list->content;
		was_killed = ft_here_doc_cmd(ctx, cmd);
		cmd_list = cmd_list->next;
	}
	return (was_killed);
}

bool	ft_here_doc(t_ctx *ctx)
{
	bool	is_syntax_error;
	bool	killed;

	is_syntax_error = false;
	killed = false;
	if (ft_is_syntax_error_pipe(ctx->line))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'pipe'", 2);		
		ctx->last_error = 2;
		is_syntax_error = true;
	}
	killed = ft_manage_here_doc(ctx);
	if (killed)
		ctx->last_error = 130;
	if (!killed && ft_is_syntax_error_redir(ctx->line))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'redir'", 2);
		ctx->last_error = 2;
		is_syntax_error = true;
	}
	return (is_syntax_error | killed);
}
