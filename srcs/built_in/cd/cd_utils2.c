/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 10:21:01 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/08 10:52:20 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "built_in.h"

#include <stdbool.h>

void    ft_set_pwd(t_ctx *ctx, char **argv)
{
    char    *tmp_pwd;
    
    if (argv[1][0] == '.' && argv[1][1] == '.')
        tmp_pwd = getcwd(NULL, 0);
    else if (argv[1][0] == '.')
    {
        tmp_pwd = ft_strdup(ft_get_entry_ptr(ctx, "PWD"));
        if (!tmp_pwd)
            ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
    }
    else
    {
        tmp_pwd = ft_strdup(argv[1]);
        if (!tmp_pwd)
            ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
    }
    ft_free_double(&argv);
    ft_replace_entry_value(ctx, "PWD", tmp_pwd);
}
