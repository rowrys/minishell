/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:38 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/12 14:12:49 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <unistd.h>

static void	ft_change_dir(t_ctx *ctx, bool is_child, char **argv)
{
	char	*current;
	char	*next;

	current = getcwd(NULL, 0);
	if (chdir(argv[1]) == -1)
	{
		if (is_child)
			ft_free_lst_db_strs(NULL, argv, current, NULL);
		ft_cd_error(is_child, ctx, CHDIR_ERROR, 2);
	}
	ft_repl_entry_value(ctx, "OLDPWD", current, argv);
	next = getcwd(NULL, 0);
	if (!next)
	{
		ft_cd_no_parent(argv, current, ctx, is_child);
		return ;
	}
	ft_repl_entry_value(ctx, "PWD", next, argv);
	if (is_child)
		ft_destroy_ctx(ctx);
	if (is_child)
		exit(EXIT_SUCCESS);
	ft_free_double(&argv);
	ctx->last_error = EXIT_SUCCESS;
}

static char	*ft_join_path(t_ctx *ctx, char *path, char **argv)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin("/", argv[1]);
	if (!result && argv[1])
	{
		free(path);
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	if (path)
	{
		tmp = result;
		result = ft_strjoin(path, tmp);
		free(tmp);
		free(path);
		if (!result)
			ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	return (result);
}

static void	ft_cd_current_dir(t_ctx *ctx, bool is_child, char *path,
		char **argv)
{
	char	*tmp_path;
	char	*pwd;

	tmp_path = ft_join_path(ctx, path, argv);
	ft_free_double(&argv);
	pwd = getcwd(NULL, 0);
	if (chdir(tmp_path) == -1)
	{
		ft_free_lst_db_strs(NULL, argv, tmp_path, pwd);
		ft_cd_error(is_child, ctx, CHDIR_ERROR, 2);
		return ;
	}
	if (!pwd)
		pwd = ft_strdup(ft_get_entry_ptr(ctx, "PWD"));
	if (!pwd && ft_get_entry_ptr(ctx, "PWD"))
		ft_free_and_error(tmp_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_repl_entry_value(ctx, "OLDPWD", pwd, NULL);
	ft_repl_entry_value(ctx, "PWD", tmp_path, NULL);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	ctx->last_error = EXIT_SUCCESS;
}

void	ft_cd(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	char	**split_path;
	char	*cdpath;

	if (ft_is_valid_cd(ctx, is_child, argc, argv) == false)
		return ;
	if (*argv[1] == '/' || *argv[1] == '.')
	{
		ft_change_dir(ctx, is_child, argv);
		return ;
	}
	cdpath = ft_get_entry_ptr(ctx, "CDPATH");
	if (!cdpath)
	{
		cdpath = getcwd(NULL, 0);
		if (cdpath)
			ft_cd_current_dir(ctx, is_child, cdpath, argv);
		else
			ft_cd_no_parent(argv, NULL, ctx, is_child);
		return ;
	}
	split_path = ft_split(cdpath, ':');
	if (!split_path)
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_manage_cdpath(ctx, is_child, split_path, argv);
}
