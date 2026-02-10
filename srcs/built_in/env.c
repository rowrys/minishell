/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 19:54:04 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/10 08:54:15 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>

static void	ft_builtin_error(t_ctx *ctx, bool is_clone)
{
	if (is_clone)
		ft_error(ctx, "format: env: do not add arguments", 2);
	ctx->last_error = EXIT_FAILURE;
	ft_putstr_fd("format: env: do not add arguments\n", 2);
}

void	ft_env(t_ctx *ctx, bool is_clone, size_t argc, char **argv)
{
	t_list			*env_dict;
	t_dict_entry	*entry;

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
		ft_putstr_fd(entry->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(entry->value, 1);
		env_dict = env_dict->next;
	}
	if (is_clone)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	ctx->last_error = EXIT_SUCCESS;
}
