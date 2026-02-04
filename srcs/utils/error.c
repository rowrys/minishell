/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:17:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/04 10:22:00 by mcolin           ###   ########.fr       */
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

void    ft_cmd_not_found(t_ctx *ctx, char *binary, char **env)
{
    pid_t   cpid;
    char    **bin_tmp;
	int		status;

	if (access("/usr/lib/command-not-found", X_OK) != 0)
	{
		ft_free_double(&env);
		ft_putstr_fd("minishell: ", 2);
		ft_error(ctx, binary, EXIT_CMD_NOT_FOUND);
	}
	cpid = fork();
    if (cpid == -1)
        ft_free_db_and_error(env, ctx, "Fork :", EXIT_FAILURE);
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(binary, 2);
	ft_putendl_fd(": Permission denied", 2);
	ft_destroy_ctx(ctx);
	exit(EXIT_PERMISSION_DENIED);
}

void    ft_error(t_ctx *ctx, char *msg, int code)
{
    char    *msg_cpy;

    msg_cpy = ft_strdup(msg);
    if (!msg_cpy && msg)
        ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
    ft_destroy_ctx(ctx);
    if (code == 2)
    {
        ft_putendl_fd(msg_cpy, 2);
        code = 1;
    }
    else
        perror(msg_cpy);
    free(msg_cpy);
    exit(code);
}