/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:30:38 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 17:49:32 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <unistd.h>

#define NO_DIRECTORY "minishell: cd: No such file or directory"
#define NO_PARENT_DIR "cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory"

static void	ft_cd_switch(t_ctx *ctx, bool is_child, char *key1, char *key2)
{
	char	*ptr_pwd;
	char	*ptr_oldpwd;

	ptr_oldpwd = ft_get_entry_ptr(ctx, key1);
	if (!ptr_oldpwd)
	{
		ft_cd_error(is_child, ctx, "minishell: cd: OLDPWD not set", 2);
		return ;
	}
	if (chdir(ptr_oldpwd) == -1)
		ft_cd_error(is_child, ctx, NO_DIRECTORY, EXIT_FAILURE);
	ptr_pwd = ft_get_entry_ptr(ctx, key2);
	ft_replace_entry_value(ctx, "PWD", ptr_oldpwd);
	ft_replace_entry_value(ctx, "OLDPWD", ptr_pwd);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	ctx->last_error = EXIT_SUCCESS;
}

static void	ft_only_cd(t_ctx *ctx, bool is_child)
{
	char	*tmp_pwd;
	char	*ptr_oldpwd;
	char	*tmp_home;

	tmp_home = ft_get_entry_ptr(ctx, "HOME");
	if (!tmp_home)
		ft_cd_error(is_child, ctx, "minishell: cd: HOME not set", 2);
	tmp_home = ft_strdup(tmp_home);
	if (!tmp_home)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	tmp_pwd = ft_get_entry_ptr(ctx, "PWD");
	ft_replace_entry_value(ctx, "PWD", tmp_home);
	ptr_oldpwd = ft_get_entry_ptr(ctx, "OLDPWD");
	ft_replace_entry_value(ctx, "OLDPWD", tmp_pwd);
	free(ptr_oldpwd);
	if (chdir(tmp_home) == -1)
		ft_cd_error(is_child, ctx, NO_DIRECTORY, EXIT_FAILURE);
	else if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	else
		ctx->last_error = EXIT_SUCCESS;
}

static bool	ft_is_valid(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	if (argc == 2 && (argv[1][1] || argv[1][0] != '-'))
		return (true);
	ft_free_double(&argv);
	if (argc > 2)
		ft_cd_error(is_child, ctx, "minishell: cd: too many arguments", 2);
	else if (argc == 1)
		ft_only_cd(ctx, is_child);
	else
	{
		if (!ft_get_entry_ptr(ctx, "OLDPWD"))
			ft_cd_error(is_child, ctx, "minishell: cd: HOME not set", 2);
		else
			ft_cd_switch(ctx, is_child, "OLDPWD", "PWD");
		if (is_child)
			ft_destroy_ctx(ctx);
		if (is_child)
			exit(EXIT_SUCCESS);
		ctx->last_error = EXIT_SUCCESS;
	}
	return (false);
}

static void	ft_chdir_argv(t_ctx *ctx, bool is_child, char **argv)
{
	char	*tmp;

	if (chdir(argv[1]) == -1)
	{
		ft_free_double(&argv);
		ft_cd_error(is_child, ctx, NO_DIRECTORY, EXIT_FAILURE);
	}
	else if (ft_is_valid_parent(argv[1]) == false)
	{
		ft_free_double(&argv);
		ft_cd_error(is_child, ctx, NO_PARENT_DIR, EXIT_FAILURE);
	}
	else
	{
		tmp = ft_get_entry_ptr(ctx, "OLDPWD");
		ft_replace_entry_value(ctx, "OLDPWD", ft_get_entry_ptr(ctx, "PWD"));
		free(tmp);
		ft_set_pwd(ctx, argv);
		if (is_child)
		{
			ft_destroy_ctx(ctx);
			exit(EXIT_SUCCESS);
		}
		ctx->last_error = EXIT_SUCCESS;
	}
}

void	ft_cd(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	char	**cd_path;
	char	*tmp_cdpath;

	if (ft_is_valid(ctx, is_child, argc, argv) == false)
		return ;
	if (*argv[1] == '/' || *argv[1] == '.')
	{
		ft_chdir_argv(ctx, is_child, argv);
		return ;
	}
	tmp_cdpath = ft_get_entry_ptr(ctx, "CDPATH");
	if (!tmp_cdpath)
	{
		tmp_cdpath = getcwd(NULL, 0);
		ft_cd_check_dir(ctx, is_child, tmp_cdpath, argv);
		return ;
	}
	cd_path = NULL;
	cd_path = ft_split(tmp_cdpath, ':');
	if (!cd_path)
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_manage_cdpath(ctx, is_child, cd_path, argv);
}
