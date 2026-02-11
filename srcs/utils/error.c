/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:17:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/11 14:00:54 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "execute.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_cd_error(bool is_child, t_ctx *ctx, char *msg, int code)
{
	if (is_child)
		ft_error(ctx, msg, code);
	if (msg && code != 2)
		ft_putendl_fd(msg, 2);
	if (code == 2)
	{
		if (msg)
			ft_putstr_fd(msg, 2);
		perror(NULL);
		code = EXIT_FAILURE;
	}
	ctx->last_error = code;
}

static char	**ft_get_bin_tmp(t_ctx *ctx, char *binary, char **env)
{
	char	**result;

	result = ft_calloc(3, sizeof(char *));
	if (!result)
	{
		ft_free_double(&env);
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	result[0] = ft_strdup("command-not-found");
	if (!*result)
	{
		free(result);
		ft_free_double(&env);
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	result[1] = ft_strdup(binary);
	if (!*result)
	{
		ft_free_double(&result);
		ft_free_double(&env);
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	return (result);
}

void	ft_cmd_not_found(t_ctx *ctx, char *binary, char **env)
{
	pid_t	cpid;
	char	**bin_tmp;
	int		status;

	if (access("/usr/lib/command-not-found", X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_free_db_and_error(env, ctx, binary, EXIT_CMD_NOT_FOUND);
	}
	cpid = fork();
	if (cpid == -1)
		ft_free_db_and_error(env, ctx, "Fork: ", EXIT_FAILURE);
	if (cpid == 0)
	{
		bin_tmp = ft_get_bin_tmp(ctx, binary, env);
		ft_destroy_ctx(ctx);
		execve("/usr/lib/command-not-found", bin_tmp, env);
		free(bin_tmp);
		ft_free_db_and_error(env, NULL, "minishell: ", EXIT_FAILURE);
	}
	waitpid(cpid, &status, 0);
	status = ft_check_status(status);
	ft_free_double(&env);
	ft_destroy_ctx(ctx);
	exit(status);
}

void	ft_error_execve(t_ctx *ctx, char *msg, int errno_tmp)
{
	ft_putstr_fd("minishell: ", 2);
	if (errno_tmp == ENOENT || errno_tmp == EACCES || errno_tmp == EISDIR)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	free(msg);
	errno = errno_tmp;
	if (errno_tmp == ENOENT)
		ft_error(ctx, NULL, EXIT_CMD_NOT_FOUND);
	else if (errno_tmp == EACCES || errno_tmp == EISDIR)
		ft_error(ctx, NULL, EXIT_PERMISSION_DENIED);
	ft_error(ctx, "execve: ", EXIT_FAILURE);
}

void	ft_error(t_ctx *ctx, char *msg, int code)
{
	char	*msg_cpy;
	int		errno_tmp;

	errno_tmp = errno;
	msg_cpy = ft_strdup(msg);
	if (!msg_cpy && msg)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_destroy_ctx(ctx);
	if (code == 2 || errno_tmp == EXIT_SUCCESS)
	{
		if (msg)
			ft_putendl_fd(msg_cpy, 2);
		code = EXIT_FAILURE;
	}
	else
	{
		errno = errno_tmp;
		perror(msg_cpy);
	}
	free(msg_cpy);
	exit(code);
}
