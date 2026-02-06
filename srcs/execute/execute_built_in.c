/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:58:18 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/06 18:26:35 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"
#include "execute.h"
#include "utils.h"

#include <stddef.h>

#define CHILD  1
#define PARENT 0

static int	ft_built_in(t_ctx *ctx, t_cmd *cmd, t_built_in built_in_type)
{
	const static void		(*built_in_fonction[])(t_ctx *, bool, char**) = {
		&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit
	};
	int						status;
	char					**args;
	int						tmp_std_fileno[2];

	tmp_std_fileno[0] = dup(STDIN_FILENO);
	tmp_std_fileno[1] = dup(STDOUT_FILENO);
	if (ft_dup(cmd->fd_in, STDIN_FILENO) == -1)
		ft_error(ctx, "dup: ", EXIT_FAILURE);
	if (ft_dup(cmd->fd_out, STDOUT_FILENO) == -1)
		ft_error(ctx, "dup: ", EXIT_FAILURE);
	args = ft_cmd_to_arg(ctx, cmd);
	if (cmd->cpid == -2)
		built_in_fonction[built_in_type - 1](ctx, PARENT, args);
	else
		built_in_fonction[built_in_type - 1](ctx, CHILD, args);
	if (ft_dup(tmp_std_fileno[0], STDIN_FILENO) == -1)
		ft_free_db_error(args, ctx, "dup: ", EXIT_FAILURE);
	if (ft_dup(tmp_std_fileno[1], STDOUT_FILENO) == -1)
		ft_free_db_error(args, ctx, "dup: ", EXIT_FAILURE);
	ft_free_double(&args);
	return (status);
}

void	ft_execute_built_in(t_ctx *ctx, t_cmd *cmd, t_built_in built_in_type)
{
	if (cmd->cpid == -2)
	{
		ft_manage_redir(ctx, cmd, REDIR_BUILT_IN);
		ft_built_in(ctx, cmd, built_in_type);
	}
	else if (cmd->cpid == 0)
	{
		ft_signal_child();
		ft_manage_redir(ctx, cmd, REDIR_FORKED);
		ft_built_in(ctx, cmd, built_in_type);
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	cmd->pipe_cmd[0] = -1;
	ft_close_cmd_fds(cmd);
}
