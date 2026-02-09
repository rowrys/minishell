/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 10:21:01 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 19:15:11 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <linux/limits.h>
#include <stdbool.h>

#define NO_PARENT_DIR "cd: error retrieving current directory: getcwd: "

bool	ft_is_valid_parent(char *parent)
{
	if (*parent == '.')
	{
		if (parent[1] && access(parent, F_OK) == -1)
			return (false);
		if (parent[1] == '.' && !parent[2] && access(parent, F_OK) == -1)
			return (false);
	}
	return (true);
}

void	ft_set_pwd(t_ctx *ctx, char **argv)
{
	char	tmp_pwd[PATH_MAX];
	char	*ptr_pwd;

	ptr_pwd = NULL;
	if (argv[1][0] == '.' && argv[1][1] == '.')
	{
		if (!getcwd(tmp_pwd, PATH_MAX))
			ft_free_db_and_error(argv, ctx, NO_PARENT_DIR, EXIT_FAILURE);
	}
	else if (argv[1][0] == '.')
	{
		if (!getcwd(tmp_pwd, PATH_MAX))
			ft_free_db_and_error(argv, ctx, NO_PARENT_DIR, EXIT_FAILURE);
		ptr_pwd = ft_strdup(ft_get_entry_ptr(ctx, "PWD"));
		if (!ptr_pwd)
			ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	else
	{
		ptr_pwd = ft_strdup(argv[1]);
		if (!ptr_pwd)
			ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	ft_free_double(&argv);
	ft_replace_entry_value(ctx, "PWD", ptr_pwd);
}
