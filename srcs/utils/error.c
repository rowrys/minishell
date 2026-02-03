/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:17:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 21:44:22 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "ctx.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static char	**ft_get_bin_tmp(t_ctx *ctx, char *binary, char **env)
{
	char	**result;

	result = ft_calloc(3, sizeof(char *));
	if (!result)
	{
		ft_free_double(&env);
		ft_error(ctx, "Malloc exploded, how did you do that???", EXIT_FAILURE);
	}
	result[0] = ft_strdup("command-not-found");
	if (!*result)
	{
		free(result);
		ft_free_double(&env);
		ft_error(ctx, "Malloc exploded, how did you do that???", EXIT_FAILURE);
	}
	result[1] = ft_strdup(binary);
	if (!*result)
	{
		ft_free_double(&result);
		ft_free_double(&env);
		ft_error(ctx, "Malloc exploded, how did you do that???", EXIT_FAILURE);
	}
	return (result);
}

void	ft_free_and_error(char **to_free, t_ctx *ctx, char *msg, int code)
{
	ft_free_double(&to_free);
	ft_error(ctx, msg, code);
}

void    ft_cmd_not_found(t_ctx *ctx, char *binary, char **env)
{
    pid_t   cpid;
    char    **bin_tmp;
	int		status;

	if (access("/usr/lib/command-not-found", X_OK) != 0)
	{
		ft_free_double(&env);
		ft_error(ctx, binary, EXIT_CMD_NOT_FOUND);
	}
	cpid = fork();
    if (cpid == -1)
        ft_free_and_error(env, ctx, "Fork :", EXIT_FAILURE);
    if (cpid == 0)
    {
        bin_tmp = ft_get_bin_tmp(ctx, binary, env);
        ft_destroy_ctx(ctx);
        execve("/usr/lib/command-not-found", bin_tmp, env);
        free(bin_tmp);
		ft_free_double(&env);
        ft_error(NULL, "Execve :", EXIT_FAILURE);
    }
    else
		waitpid(cpid, &status, 0);
}

void	ft_access_denied(t_ctx *ctx, char **splited_path, char *binary, char **env)
{
	ft_free_double(&env);
	ft_free_double(&splited_path);
	ft_putstr_fd(binary, 2);
	ft_putendl_fd(": Permission denied\n", 2);
	ft_destroy_ctx(ctx);
	exit(EXIT_PERMISSION_DENIED);
}

void    ft_error(t_ctx *ctx, char *msg, int code)
{
	ft_destroy_ctx(ctx);
	if (code == EXIT_CMD_NOT_FOUND)
	{
		ft_putstr_fd(msg, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (code == EXIT_FAILURE)
	    perror(msg);
	else
	{
		ft_putendl_fd(msg, 2);
		code = EXIT_FAILURE;
	}
	exit(code);
}