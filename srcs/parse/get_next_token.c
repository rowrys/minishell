/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 09:59:30 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/26 10:34:58 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "utils.h"

static char *ft_get_value(t_ctx *ctx, t_key key, size_t *i)
{
    size_t  size;
    char    *value;
    char    *line;
    
    size = 0;
    if (key != KEY_CHUNK)
        *i += ft_skip(ctx->line + *i, REDIR_SKIP);
    line = ctx->line + *i;
    while (!ft_strchr(TOKEN_LIMITER, line[size]))
    {
        if (line[size] == '\'' || line[size] == '"')
               size += ft_go_to(&line[size + 1], line[size]) + 2;
        else
            size++;
    }
    value = ft_substr(ctx->line, *i, size);
    // if (!value)
    //     ft_error(malloc);
    *i += size;
    return (value);
}

t_list *ft_get_next_token(t_ctx *ctx, t_key key, size_t *i)
{
    t_list  *new_node;
    t_token *new_token;

    new_token = ft_calloc(1, sizeof(t_token));
    // if (!new_token)
    //     ft_error(malloc);
    new_token->type = key;
    if (key == KEY_REDIR)
        new_token->type = ft_get_redir_key(ctx->line + *i);
    if (key != KEY_PIPE)
        new_token->value = ft_get_value(ctx, key, i);
    new_node = ft_lstnew(new_token);
    // if (!new_node)
    //     ft_error(malloc);
    if (key == KEY_PIPE)
        (*i)++;
    return (new_node);
}
