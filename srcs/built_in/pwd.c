/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:26:46 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 09:21:17 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <linux/limits.h>
#include <stdbool.h>

void	ft_pwd(t_ctx *ctx, bool is_clone, size_t argc, char **argv)
{
	char	buffer[PATH_MAX];

	(void)argc;
	ft_free_double(&argv);
	if (!getcwd(buffer, PATH_MAX))
		ft_putendl_fd(ft_get_entry_ptr(ctx, "PWD"), 1);
	else
		ft_putendl_fd(buffer, 1);
	if (is_clone)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	ctx->last_error = EXIT_SUCCESS;
}
