/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:03:48 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/23 14:50:46 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static char *ft_add_next_part(t_ctx *ctx, char *chunk, size_t *i, char *result)
{
    char    *part;
    size_t	size;

    if (chunk[*i] == '"')
    {
        part = ft_get_part(ctx, &chunk[*i + 1], '"');
        part = ft_manage_expand(ctx, part, 0);
    }
    else if (chunk[*i] == '\'')
        part = ft_get_part(ctx, &chunk[*i + 1], '\'');
    else
	{
		size = 0;
		while (chunk[*i + size] && !ft_strchr(ISSPACE, chunk[*i + size]))
			size++;
		part = ft_substr(&chunk[*i], 0, size);
		// if (!part)
		// 	ft_error(ctx, "malloc error", 1);
		*i += size;
	}
    result = ft_add_part(ctx, result, part);
	return (result);
}

static void ft_addback_chunk(t_ctx *ctx, t_list **new_list, t_token *old_token)
{
    char    *chunk;
    char    *result;
    size_t  i;

    result = NULL;
    i = 0;
    chunk = ft_manage_expand(ctx, old_token->value, 1);
	if (old_token->type != KEY_PIPE && old_token->type != KEY_CHUNK
			&& (size_t)ft_skip(chunk, ISSPACE) == ft_strlen(chunk))
	{
		ft_add_token(ctx, new_list, old_token->type, NULL);
		free(chunk);
		return ;
	}
    while (chunk && chunk[i])
    {
        i += ft_skip(&chunk[i], ISSPACE);
        if (chunk[i])
            result = ft_add_next_part(ctx, chunk, &i, result);
        ft_add_token(ctx, new_list, old_token->type, result);
    }
    free(chunk);
}

t_list *ft_parse_token_list(t_ctx *ctx, t_list *old_lst)
{
    t_list  *new_list;
    t_token *old_token;

    new_list = NULL;
    while (old_lst)
    {
        old_token = old_lst->content;
        if (old_token->type == KEY_PIPE)
			ft_add_token(ctx, &new_list, KEY_PIPE, NULL);
        else if (old_token->type == KEY_CHUNK)
            ft_addback_chunk(ctx, &new_list, old_token);
        else
            ft_addback_newlst(ctx, &new_list, old_token);
        old_lst = old_lst->next;
    }
    return (new_list);
}
