/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 22:54:01 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/12 13:16:06 by mcolin           ###   ########.fr       */
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

static void	ft_chdir_cdpath(t_ctx *ctx, bool is_child, char *path, char **argv)
{
	char	*tmp;

	ft_free_double(&argv);
	tmp = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_free_lst_db_strs(NULL, NULL, tmp, path);
		ft_cd_error(is_child, ctx, CHDIR_ERROR, 2);
		return ;
	}
	ft_repl_entry_value(ctx, "OLDPWD", tmp, NULL);
	ft_repl_entry_value(ctx, "PWD", path, NULL);
	ft_putendl_fd(path, 1);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
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
