/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:52:15 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 16:01:33 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parse.h"
#include "utils.h"
#include <assert.h>
#include <readline/chardefs.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_add_command(t_ctx *ctx)
{
	t_cmd	*new_cmd;
	t_list	*new_node;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	// if (!new_cmd)
	// 	ft_error(ctx, "malloc error", 1);
	new_node = ft_lstnew(new_cmd);
	// if (!new_node->content)
	// 	ft_error(ctx, "malloc error", 1);
	ft_lstadd_back(&ctx->cmd_lst, new_node);
}

static	t_cmd	*ft_init_cmd(t_ctx *ctx)
{
	t_cmd	*new_cmd;
	
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	new_cmd->pipe_hd[0] = -1;
	new_cmd->pipe_hd[1] = -1;
	new_cmd->pipe_cmd[0] = -1;
	new_cmd->pipe_cmd[1] = -1;
	new_cmd->cpid = -2;
	return (new_cmd); 
}


static t_cmd	*ft_get_next_cmd(t_ctx *ctx, size_t *i)
{
	t_list	*new_node;
	t_cmd	*new_cmd;
	
	new_cmd = ft_init_cmd(ctx);
	while (true)
	{
    	*i += ft_skip(ctx->line + *i, ISSPACE);
		if (!ctx->line[*i])
			break ;
		if (ctx->line[*i] == '|')
		{
			new_node = ft_get_next_token(ctx, KEY_PIPE, i);
			ft_lstadd_back(&(new_cmd->token), new_node);	
			break ;
		}
		else if (ctx->line[*i] == '<' || ctx->line[*i] == '>')
			new_node = ft_get_next_token(ctx, KEY_REDIR, i);
		else
			new_node = ft_get_next_token(ctx, KEY_CHUNK, i);
		ft_lstadd_back(&(new_cmd->token), new_node);	
	}
	return (new_cmd);
}

void	ft_parse_line(t_ctx *ctx)
{
	t_list	*new_node;
	t_cmd	*new_cmd;
	size_t	i;

	i = 0;
	while (ctx->line[i])
	{
		new_cmd = ft_get_next_cmd(ctx, &i);
		new_node = ft_lstnew(new_cmd);
		if (!new_node)
			ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
		ft_lstadd_back(&ctx->cmd_lst, new_node);
	}
}
