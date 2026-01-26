/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:03:48 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/26 14:31:40 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static void ft_add_ambigous_redir(t_ctx *ctx, t_list **new_list, t_key key, char *to_free)
{
    ft_add_token(ctx, new_list, key, NULL);
	free(to_free);
}

static void ft_add_next_part(t_ctx *ctx, char *chunk, size_t *i, char **result)
{
    char    *part;
    size_t  size;

    size = 0;
    while (true)
	{	
        if (!chunk[*i + size] || ft_strchr(ISSPACE, chunk[*i + size])
            || chunk[*i + size] == '"' || chunk[*i + size] == '\'')
        {
            part = ft_substr(&chunk[*i], 0, size);
            // if (!part)
	        // 	ft_error(ctx, "malloc error", 1);
            *result = ft_add_part(ctx, *result, part);
            *i += size;
            if (!chunk[*i] || ft_strchr(ISSPACE, chunk[*i]))
                return ;
            size = -1;
            part = ft_get_part(ctx, &chunk[*i + 1], chunk[*i]);
            if (chunk[*i] == '"')
                part = ft_manage_expand(ctx, part, 0);
            *result = ft_add_part(ctx, *result, part);
            *i += ft_go_to(&chunk[*i + 1], chunk[*i]) + 2;
        }
		size++;
    }
}

static void ft_addback_chunk(t_ctx *ctx, t_list **new_list, t_token *old_token,
    char *value)
{
    char    *chunk;
    char    *result;
    size_t  i;

    i = 0;
    chunk = ft_manage_expand(ctx, value, 1);
	if (ft_is_redir_key(old_token->type) && ft_chunk_is_empty(chunk, i))
	{
		ft_add_ambigous_redir(ctx, new_list, old_token->type, chunk);
		return ;
	}
    while (chunk && chunk[i])
    {
        result = NULL;
        i += ft_skip(&chunk[i], ISSPACE);
        if (chunk[i])
            ft_add_next_part(ctx, chunk, &i, &result);
        if (ft_is_redir_key(old_token->type) && !ft_chunk_is_empty(chunk, i))
        {
            ft_add_ambigous_redir(ctx, new_list, old_token->type, result);
            return ;
        }
        ft_add_token(ctx, new_list, old_token->type, result);
    }
    free(chunk);
}

t_list *ft_parse_token_list(t_ctx *ctx, t_list *old_lst)
{
    t_list  *new_list;
    t_token *old_token;
    char    *value;

    new_list = NULL;
    while (old_lst)
    {
        old_token = old_lst->content;
        value = ft_strdup(old_token->value);
        // if (!value)
        //     ft_error(malloc);
        if (old_token->type == KEY_PIPE)
        {
            free (value);
            ft_add_token(ctx, &new_list, KEY_PIPE, NULL);
        }
        else if (old_token->type == KEY_HERE_DOC)
            ft_add_token(ctx, &new_list, KEY_HERE_DOC, value);
        else
            ft_addback_chunk(ctx, &new_list, old_token, value);
        old_lst = old_lst->next;
    }
    return (new_list);
}
