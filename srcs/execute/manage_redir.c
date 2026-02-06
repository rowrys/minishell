/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:04:57 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/06 09:34:50 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "execute.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static void ft_redir_error(t_ctx *ctx, char *value, int mode)
{
    if (mode == REDIR_FORGOTTEN)
    {
        ft_destroy_ctx(ctx);
        exit(EXIT_FAILURE);
    }
    else if (value)
    {
        ft_putstr_fd(value, 2);
        if (mode == REDIR_FORKED)
            ft_error(ctx, ": ", EXIT_FAILURE);
        ft_putendl_fd(": ", 2);
    }
    else
    {
        if (mode == REDIR_FORKED)
            ft_error(ctx, "minishell: ambiguous redirect", 2);
        ft_putendl_fd("minishell: ambiguous redirect", 2);
    }
    ctx->last_error = EXIT_FAILURE;
}

static bool	ft_redir(t_cmd *cmd, t_token *token)
{
    if (token->type == KEY_LREDIR)
    {
        ft_close(&cmd->fd_in);
        if (token->value)
            cmd->fd_in = open(token->value, O_RDONLY);
        if (cmd->fd_in < 0)
            return (false);
        return (true);
    }
    else
    {
        ft_close(&cmd->fd_out);
        if (token->type == KEY_APPEND && token->value)
            cmd->fd_out = open(token->value, O_WRONLY | O_CREAT | O_APPEND,
        		    0644);
        else if (token->value)
            cmd->fd_out = open(token->value, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
    }
    if (cmd->fd_out < 0)
            return (false);
    return (true);
}

static int  ft_get_index_last_here_doc(t_cmd *cmd)
{
    t_list  *token_lst;
    t_token *token;
    int     last_here_doc;
    int     i;
    
    i = 0;
    last_here_doc = -1;
    token_lst = cmd->token;
    while (token_lst)
    {
        token = token_lst->content;
        if (token->type == KEY_HERE_DOC)
            last_here_doc = i;
        i++;
        token_lst = token_lst->next;
    }
    return (last_here_doc);
}

void    ft_manage_redir(t_ctx *ctx, t_cmd *cmd, int mode)
{
    t_list  *token_lst;
    t_token *token;
    size_t  i;
    size_t  index_last_here_doc;

    index_last_here_doc = ft_get_index_last_here_doc(cmd);
    token_lst = cmd->token;
    i = 0;
    while (token_lst)
    {
        token = token_lst->content;
        if (ft_is_redir_key(token->type) && token->type != KEY_HERE_DOC
            && ft_redir(cmd, token) == false)
            ft_redir_error(ctx, token->value, mode);
        if (i == index_last_here_doc)
        {
            ft_replace_fd(&cmd->fd_in, cmd->pipe_hd[0]);
            cmd->pipe_hd[0] = -1;
        }
        i++;
        token_lst = token_lst->next;
    }
}
