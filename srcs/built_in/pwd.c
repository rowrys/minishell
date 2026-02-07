/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:26:46 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/07 23:46:14 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"
#include "utils.h"

#include <stdbool.h>
#include <linux/limits.h>

void    ft_pwd(t_ctx *ctx, bool is_clone, size_t argc, char **argv)
{
    char    buffer[PATH_MAX];

    (void)argc;
    ft_free_double(&argv);
    if (!getcwd(buffer, PATH_MAX))
    {
        if (is_clone)
            ft_error(ctx, "minishell: pwd: size limit: PATH_MAX", 2);
        ft_putendl_fd("minishell: pwd: size limit: PATH_MAX", 2);
        ctx->last_error = EXIT_FAILURE;
        return ;
    }
    ft_putendl_fd(buffer, 1);
    if (is_clone)
    {
        ft_destroy_ctx(ctx);
        exit(EXIT_SUCCESS);
    }
    ctx->last_error = EXIT_SUCCESS;
}
