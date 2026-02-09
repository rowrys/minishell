/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:32:18 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 08:49:52 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "minishell.h"
#include "sig.h"
#include "utils.h"

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELTA_SIG_STATUS 0xFF - 0x7F

int	ft_check_status(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + DELTA_SIG_STATUS);
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status) + DELTA_SIG_STATUS);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

static void	ft_wait(t_ctx *ctx)
{
	t_list	*cmd_lst;
	t_cmd	*cmd;
	bool	have_sigint;
	int		status;

	/* à insérer dans le code pour de potentielle conditional jump*/
	// status = 0;
	/*                                                            */
	cmd_lst = ctx->cmd_lst;
	have_sigint = false;
	while (cmd_lst)
	{
		cmd = cmd_lst->content;
		if (cmd->cpid != -2)
		{
			waitpid(cmd->cpid, &status, 0);
			if (status == SIGINT)
				have_sigint = true;
			ctx->last_error = ft_check_status(status);
		}
		cmd_lst = cmd_lst->next;
	}
	if (have_sigint)
		write(1, "\n", 1);
	if (ctx->last_error == SIGQUIT + DELTA_SIG_STATUS)
		write(2, "^\\Quit\n", 7);
}

static void	ft_fork(t_ctx *ctx, t_cmd *cmd)
{
	cmd->cpid = fork();
	if (cmd->cpid == -1)
		ft_error(ctx, "fork: ", EXIT_FAILURE);
	else if (cmd->cpid == 0)
	{
		ft_signal_child();
		ft_execute_cmd(ctx, cmd);
	}
	cmd->pipe_cmd[0] = -1;
	ft_close_cmd_fds(cmd);
}

static void	ft_pipe(t_ctx *ctx, t_cmd *cmd, t_cmd *next_cmd)
{
	if (pipe(cmd->pipe_cmd) == -1)
		ft_error(ctx, "pipe: ", EXIT_FAILURE);
	cmd->fd_out = cmd->pipe_cmd[1];
	next_cmd->fd_in = cmd->pipe_cmd[0];
	cmd->pipe_cmd[1] = -1;
}

void	ft_execute(t_ctx *ctx)
{
	t_list	*cmd_lst;
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	bool	is_piped;

	cmd_lst = ctx->cmd_lst;
	is_piped = false;
	while (cmd_lst)
	{
		current_cmd = cmd_lst->content;
		if (cmd_lst->next)
		{
			is_piped = true;
			next_cmd = cmd_lst->next->content;
			ft_pipe(ctx, current_cmd, next_cmd);
			ft_fork(ctx, current_cmd);
		}
		else if (is_piped)
			ft_fork(ctx, current_cmd);
		else
			ft_execute_cmd(ctx, current_cmd);
		cmd_lst = cmd_lst->next;
	}
	ft_wait(ctx);
}
