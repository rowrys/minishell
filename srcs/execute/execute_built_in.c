/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:58:18 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/07 20:38:52 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ctx.h"
#include "execute.h"
#include "utils.h"
#include "sig.h"
#include "built_in.h"

#include <stddef.h>

#define CHILD  1
#define PARENT 0

static void ft_unset(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	(void)argc;
	(void)is_child;
	ft_free_db_and_error(argv, ctx, "noob", 69);
}
static void ft_export(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	(void)argc;
	(void)is_child;
	ft_free_db_and_error(argv, ctx, "noob", 69);
}

static void ft_pwd(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	(void)argc;
	(void)is_child;
	ft_free_db_and_error(argv, ctx, "noob", 69);
}

static void ft_cd(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	(void)argc;
	(void)is_child;
	ft_free_db_and_error(argv, ctx, "noob", 69);
}

static const t_builtin_func	g_built_in_function[BUILT_IN_ENUM_MAX] = 
{
	[BUILT_IN_ECHO]   = ft_echo,
	[BUILT_IN_CD]     = ft_cd,
	[BUILT_IN_PWD]    = ft_pwd,
	[BUILT_IN_EXPORT] = ft_export,
	[BUILT_IN_UNSET]  = ft_unset,
	[BUILT_IN_ENV]    = ft_env,
	[BUILT_IN_EXIT]   = ft_exit,
};

static size_t	ft_get_argc(char **argv)
{
	size_t	result;

	result = 0;
	while (argv[result])
		result++;
	return (result);
}

static void	ft_built_in(t_ctx *ctx, t_cmd *cmd, t_built_in built_in_type)
{
	char	**argv;
	int		argc;

	ctx->stdin_fileno = dup(STDIN_FILENO);
	ctx->stdout_fileno = dup(STDOUT_FILENO);
	if (ft_dup(cmd->fd_in, STDIN_FILENO) == -1)
		ft_error(ctx, "dup: ", EXIT_FAILURE);
	if (ft_dup(cmd->fd_out, STDOUT_FILENO) == -1)
		ft_error(ctx, "dup: ", EXIT_FAILURE);
	argv = ft_cmd_to_arg(ctx, cmd);
	argc = ft_get_argc(argv);
	if (cmd->cpid == -2)
		g_built_in_function[built_in_type](ctx, PARENT, argc, argv);
	else
		g_built_in_function[built_in_type](ctx, CHILD, argc, argv);
	if (ft_dup(ctx->stdin_fileno, STDIN_FILENO) == -1)
		ft_free_db_and_error(argv, ctx, "dup: ", EXIT_FAILURE);
	if (ft_dup(ctx->stdout_fileno, STDOUT_FILENO) == -1)
		ft_free_db_and_error(argv, ctx, "dup: ", EXIT_FAILURE);
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
	ft_close(&ctx->stdin_fileno);
	ft_close(&ctx->stdout_fileno);
	ft_close_cmd_fds(cmd);
}
