/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:54:04 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/06 20:40:00 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"
#include "utils.h"

#include <stdbool.h>

static void    ft_builtin_error(t_ctx *ctx, bool is_clone)
{
    if (is_clone == false)
        ft_error(ctx, "format: env: do not add arguments\n", 2);
    ctx->last_error = 2;
    ft_putstr_fd("format: env: do not add arguments\n", 2);
}

static void    ft_put_entry(t_ctx *ctx, t_dict_entry *entry)
{
    char    *result;

    result = ft_triple_join(ctx, entry->key, "=", entry->value);
    ft_putendl_fd(result, 1);
    free(result);
}

void    ft_env(t_ctx *ctx, bool is_clone, size_t argc, char **argv)
{
    t_list          *env_dict;
    t_dict_entry    *entry;

    ft_free_double(&argv);
    if (argc != 1)
    {
        ft_builtin_error(ctx, is_clone);
        return ;
    }
    env_dict = ctx->env_dict;
    while (env_dict)
    {
        entry = env_dict->content;
        ft_put_entry(ctx, entry);
        env_dict = env_dict->next;
    }
    if (is_clone)
    {
        ft_destroy_ctx(ctx);
        exit(EXIT_SUCCESS);
    }
    ctx->last_error = EXIT_SUCCESS;
}
