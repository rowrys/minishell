/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forgotten_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:04:45 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 22:07:29 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "utils.h"

#include <stdbool.h>
#include <fcntl.h>
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
		ft_manage_redir(ctx, cmd, REDIR_FORKED);
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(cmd->cpid, NULL, 0);
}


void	ft_forgotten_child(t_ctx *ctx, t_cmd *cmd)
{
	t_list	*token_list;
	t_token	*token;

	token_list = cmd->token;
	while (token_list)
	{
		token = token_list->content;
		if (ft_is_redir_key(token->type) && token->type != KEY_HERE_DOC)
		{
			if (cmd->cpid == -2)
				ft_child_fork(ctx, cmd);
			else
			{
				ft_forgotten_fork(ctx, cmd);
				ft_destroy_ctx(ctx);				
				exit(EXIT_SUCCESS);
			}
			break ;
		}
		token_list = token_list->next;
	}
	ft_close_cmd_fds(cmd);
}
