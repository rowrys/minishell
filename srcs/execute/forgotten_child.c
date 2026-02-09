/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forgotten_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:04:45 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 08:50:04 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "execute.h"
#include "libft.h"
#include "minishell.h"
#include "sig.h"
#include "utils.h"

#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>

static void	ft_forgotten_fork(t_ctx *ctx, t_cmd *cmd)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
		exit(EXIT_FAILURE);
	if (cpid == 0)
	{
		ft_signal_child();
		ft_manage_redir(ctx, cmd, REDIR_FORKED);
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
}

static void	ft_child_fork(t_ctx *ctx, t_cmd *cmd)
{
	cmd->cpid = fork();
	if (cmd->cpid == -1)
		ft_error(ctx, "fork: ", EXIT_FAILURE);
	if (cmd->cpid == 0)
	{
		ft_signal_child();
		ft_manage_redir(ctx, cmd, REDIR_FORKED);
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
}

static bool	ft_have_redir(t_cmd *cmd)
{
	t_list	*token_list;
	t_token	*token;

	token_list = cmd->token;
	while (token_list)
	{
		token = token_list->content;
		if (ft_is_redir_key(token->type) && token->type != KEY_HERE_DOC)
			return (true);
		token_list = token_list->next;
	}
	return (false);
}

void	ft_forgotten_child(t_ctx *ctx, t_cmd *cmd)
{
	if (cmd->cpid == -2)
		ft_child_fork(ctx, cmd);
	else
	{
		if (ft_have_redir(cmd))
			ft_forgotten_fork(ctx, cmd);
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	cmd->pipe_cmd[0] = -1;
	ft_close_cmd_fds(cmd);
}
