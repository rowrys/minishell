/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:17:17 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/11 12:03:47 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "ctx.h"

#include <stdbool.h>

void	ft_cd_no_parent(char **argv, char *str, t_ctx *ctx, bool is_child)
{
	if (argv)
		ft_free_double(&argv);
	if (str)
		free(str);
	if (is_child)
		ft_error(ctx, NO_PARENT_DIR, EXIT_FAILURE);
	ft_putendl_fd(NO_PARENT_DIR, 2);
	ctx->last_error = EXIT_FAILURE;
}

static void	ft_only_cd(t_ctx *ctx, bool is_child)
{
	char	*tmp;

	tmp = ft_get_entry_ptr(ctx, "HOME");
	if (!tmp)
		ft_cd_error(is_child, ctx, "minishell: cd: HOME not set", EXIT_FAILURE);
	if (!tmp)
		return ;
	tmp = getcwd(NULL, 0);
	if (!tmp || chdir(ft_get_entry_ptr(ctx, "HOME")) == -1)
	{
		ft_cd_no_parent(NULL, NULL, ctx, is_child);
		return ;
	}
	ft_repl_entry_value(ctx, "OLDPWD", tmp, NULL);
	tmp = ft_strdup(ft_get_entry_ptr(ctx, "HOME"));
	if (!tmp)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_repl_entry_value(ctx, "PWD", tmp, NULL);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	ctx->last_error = EXIT_SUCCESS;
}

static void	ft_cd_switch(t_ctx *ctx, bool is_child, char **argv)
{
	char	*current;
	char	*next;

	current = getcwd(NULL, 0);
	if (chdir(ft_get_entry_ptr(ctx, "OLDPWD")) == -1)
	{
		free(current);
		ft_cd_error(is_child, ctx, "minishell: cd: chdir: ", 2);
	}
	next = getcwd(NULL, 0);
	if (!next)
	{
		ft_cd_no_parent(argv, current, ctx, is_child);
		return ;
	}
	ft_repl_entry_value(ctx, "PWD", next, argv);
	ft_repl_entry_value(ctx, "OLDPWD", current, argv);
	ft_putendl_fd(next, 1);
	if (is_child)
		ft_destroy_ctx(ctx);
	if (is_child)
		exit(EXIT_SUCCESS);
	ctx->last_error = EXIT_SUCCESS;
}

static bool	ft_is_minus(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	if (argc == 2 && !ft_strcmp("-", argv[1]))
	{
		ft_free_double(&argv);
		if (!ft_get_entry_ptr(ctx, "OLDPWD"))
			ft_cd_error(is_child, ctx, "minishell: cd: OLDPWD not set",
				EXIT_FAILURE);
		else
			ft_cd_switch(ctx, is_child, argv);
		if (is_child)
		{
			ft_destroy_ctx(ctx);
			exit(EXIT_SUCCESS);
		}
		ctx->last_error = EXIT_SUCCESS;
		return (true);
	}
	return (false);
}

bool	ft_is_valid_cd(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	if (ft_is_minus(ctx, is_child, argc, argv))
		return (false);
	else if (argc > 2)
	{
		ft_free_double(&argv);
		ft_cd_error(is_child, ctx, "minishell: cd: too many arguments",
			EXIT_FAILURE);
		return (false);
	}
	else if (argc == 1)
	{
		ft_free_double(&argv);
		ft_only_cd(ctx, is_child);
		return (false);
	}
	return (true);
}
