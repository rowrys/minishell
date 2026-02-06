/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 09:37:13 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/06 16:03:19 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "utils.h"
#include "sig.h"

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/*
return the first chunk(the binary) otherwise
return NULL if no chunk was found
 */
static char	*ft_get_first_chunk(t_cmd *cmd)
{
	t_list	*origin;
	t_token	*token;

	origin = cmd->token;
	while (origin)
	{
		token = origin->content;
		if (token->type == KEY_CHUNK)
			return (token->value);
		origin = origin->next;
	}
	return (NULL);
}

/*
return the first chunk(the binary) otherwise
return NULL if no chunk was found
 */
static int	ft_is_built_in(char *chunk)
{
	if (!chunk)
		return (0);
	else if (!ft_strcmp(chunk, "echo"))
		return (BUILT_IN_ECHO);
	else if (!ft_strcmp(chunk, "cd"))
		return (BUILT_IN_CD);
	else if (!ft_strcmp(chunk, "pwd"))
		return (BUILT_IN_PWD);
	else if (!ft_strcmp(chunk, "export"))
		return (BUILT_IN_EXPORT);
	else if (!ft_strcmp(chunk, "unset"))
		return (BUILT_IN_UNSET);
	else if (!ft_strcmp(chunk, "env"))
		return (BUILT_IN_ENV);
	else if (!ft_strcmp(chunk, "exit"))
		return (BUILT_IN_EXIT);
	return (0);
}

static void	ft_check_fork(t_ctx *ctx, t_cmd *cmd, char *binary)
{
	if (cmd->cpid == -2)
	{
		cmd->cpid = fork();
		if(cmd->cpid == -1)
			ft_error(ctx, "fork: ", EXIT_FAILURE);
	}
	if (cmd->cpid == 0)
	{
		ft_signal_child();
		ft_execute_chunk(ctx, cmd, binary);
	}
	cmd->pipe_cmd[0] = -1;
	ft_close_cmd_fds(cmd);
}

void	ft_execute_cmd(t_ctx *ctx, t_cmd *cmd)
{
	char	*first_chunk;
	int		built_in_type;

	first_chunk = ft_get_first_chunk(cmd);
	built_in_type = ft_is_built_in(first_chunk);
	if (first_chunk && built_in_type)
		return ;
		//ft_execute_built_in(ctx, cmd, built_in_type);
	else if (first_chunk)
		ft_check_fork(ctx, cmd, first_chunk);
	else
		ft_forgotten_child(ctx, cmd);
}
