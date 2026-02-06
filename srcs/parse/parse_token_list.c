/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:03:48 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/06 09:24:27 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static void ft_add_parsed_token(t_ctx *ctx, t_list **new_list, t_token *token)
{
    char    *result;

    result = NULL;
    while (*token->value)
    {
        if (*token->value == '$')
        {
            if (!ft_parse_expand(ctx, new_list, token, &result))
                token->value += ft_explen(token->value + 1) + 1;
            else
            {
                free(result);
                return ;
            }
        }
        else if (*token->value == '"' || *token->value == '\'')
            ft_parse_quote(ctx, token, &result);
        else
            ft_parse_block(ctx, token, &result);
    }
    ft_add_token(ctx, new_list, token->type, result);
}
static bool ft_is_ambigous(t_ctx *ctx, t_list **new_list, t_token *old_token)
{
    char *value;
    
    value = ft_strdup(old_token->value);
    if (!value)
        ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
    value = ft_manage_expand(ctx, value, 1);
	if ((size_t)ft_skip(value, ISSPACE) == ft_strlen(value))
	{
		ft_add_token(ctx, new_list, old_token->type, NULL);
        free(value);
		return (true);
	}
    free(value);
    return (false);
}

static void ft_parse_token(t_ctx *ctx, t_list **new_list, t_token *old_token)
{
    t_token *tmp_token;
    char    *tmp_value;

    if (ft_is_redir_key(old_token->type) && ft_is_ambigous(ctx, new_list, old_token))
        return ;
    tmp_token = malloc(sizeof(t_token));
    if (!tmp_token)
        ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
    tmp_token->type = old_token->type;
    tmp_value= ft_strdup(old_token->value);
    if (!tmp_value)
        ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
    tmp_token->value = tmp_value;
    ft_add_parsed_token(ctx, new_list, tmp_token);
    free(tmp_value);
    free(tmp_token);
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
        if (old_token->type == KEY_PIPE)
            ft_add_token(ctx, &new_list, KEY_PIPE, NULL);
        else if (old_token->type == KEY_HERE_DOC)
        {
            value = ft_strdup(old_token->value);
            if (!value)
                ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
            ft_add_token(ctx, &new_list, KEY_HERE_DOC, value);
        }
        else
            ft_parse_token(ctx, &new_list, old_token);
        old_lst = old_lst->next;
    }
    return (new_list);
}
