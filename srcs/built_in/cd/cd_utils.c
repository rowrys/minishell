/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 22:54:01 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 09:20:39 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <sys/stat.h>

static void	ft_check_perm_denied(t_ctx *ctx, bool is_child, char **argv,
		bool perm_denied)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(argv[1], 2);
	if (perm_denied)
		ft_putendl_fd(": Permission denied", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
	ft_free_double(&argv);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_FAILURE);
	}
	ctx->last_error = EXIT_FAILURE;
}

static void	ft_perm_denied(t_ctx *ctx, bool is_child, char *path, char **argv)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(argv[1], 2);
	ft_putendl_fd(": Permission denied", 2);
	ft_free_double(&argv);
	free(path);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_FAILURE);
	}
	ctx->last_error = EXIT_FAILURE;
}

void	ft_cd_check_dir(t_ctx *ctx, bool is_child, char *path, char **argv)
{
	char	*tmp;

	tmp = ft_triple_join(ctx, path, "/", argv[1]);
	free(path);
	if ((access(tmp, X_OK) == -1))
	{
		ft_perm_denied(ctx, is_child, tmp, argv);
		return ;
	}
	ft_free_double(&argv);
	if (chdir(tmp) == -1)
	{
		free(tmp);
		ft_cd_error(is_child, ctx, NO_DIRECTORY, EXIT_FAILURE);
		return ;
	}
	free(ft_get_entry_ptr(ctx, "OLDPWD"));
	ft_replace_entry_value(ctx, "OLDPWD", ft_get_entry_ptr(ctx, "PWD"));
	ft_replace_entry_value(ctx, "PWD", tmp);
	if (is_child)
		ft_destroy_ctx(ctx);
	if (is_child)
		exit(EXIT_SUCCESS);
	ctx->last_error = EXIT_SUCCESS;
}

static void	ft_chdir_cdpath(t_ctx *ctx, bool is_child, char *cdpath,
		char **argv)
{
	char	*tmp;

	ft_free_double(&argv);
	if (chdir(cdpath) == -1)
	{
		free(cdpath);
		ft_cd_error(is_child, ctx, NO_DIRECTORY, EXIT_FAILURE);
		return ;
	}
	tmp = ft_get_entry_ptr(ctx, "OLDPWD");
	ft_replace_entry_value(ctx, "OLDPWD", ft_get_entry_ptr(ctx, "PWD"));
	free(tmp);
	tmp = ft_strdup(cdpath);
	free(cdpath);
	if (!tmp)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_replace_entry_value(ctx, "PWD", tmp);
	ft_putendl_fd(tmp, 1);
	if (is_child)
		ft_destroy_ctx(ctx);
	if (is_child)
		exit(EXIT_SUCCESS);
	ctx->last_error = EXIT_SUCCESS;
}

void	ft_manage_cdpath(t_ctx *ctx, bool is_child, char **cdpath, char **argv)
{
	struct stat	p_stat;
	char		*tmp_path;
	int			i;
	bool		perm_denied;

	i = -1;
	perm_denied = false;
	while (cdpath[++i])
	{
		tmp_path = ft_triple_join(ctx, cdpath[i], "/", argv[1]);
		if (stat(tmp_path, &p_stat) == 0 && S_ISDIR(p_stat.st_mode))
		{
			if (access(tmp_path, X_OK) == -1)
				perm_denied = true;
			else
			{
				ft_free_double(&cdpath);
				ft_chdir_cdpath(ctx, is_child, tmp_path, argv);
				return ;
			}
		}
		free(tmp_path);
	}
	ft_free_double(&cdpath);
	ft_check_perm_denied(ctx, is_child, argv, perm_denied);
}
