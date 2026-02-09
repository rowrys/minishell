/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 09:53:59 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 09:19:44 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

bool	ft_is_reg(char *bin)
{
	struct stat	bin_stat;

	if (stat(bin, &bin_stat) == 0 && S_ISREG(bin_stat.st_mode))
		return (true);
	return (false);
}

bool	ft_is_dir(char *bin)
{
	struct stat	bin_stat;

	if (stat(bin, &bin_stat) == 0 && S_ISDIR(bin_stat.st_mode))
		return (true);
	return (false);
}

char	*ft_check_bin_denied_42_angouleme(t_ctx *ctx, char **splited_path,
		size_t i, char *binary)
{
	char	*bin;
	char	*path_part;

	path_part = ft_strjoin(splited_path[i], "/");
	if (!path_part)
		ft_free_db_and_error(splited_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
	bin = ft_strjoin(path_part, binary);
	free(path_part);
	if (!bin)
		ft_free_db_and_error(splited_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
	if (bin && access(bin, F_OK) == 0 && !ft_is_dir(bin) && ft_is_reg(bin))
		return (bin);
	free(bin);
	return (NULL);
}

char	*ft_check_bin_42_angouleme(t_ctx *ctx, char **splited_path, size_t i,
		char *binary)
{
	char	*bin;
	char	*path_part;

	path_part = ft_strjoin(splited_path[i], "/");
	if (!path_part)
		ft_free_db_and_error(splited_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
	bin = ft_strjoin(path_part, binary);
	free(path_part);
	if (!bin)
		ft_free_db_and_error(splited_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
	if (bin && access(bin, X_OK) == 0 && ft_is_reg(bin) && !ft_is_dir(bin))
		return (bin);
	free(bin);
	return (NULL);
}

int	ft_dup(int fd, int fd2)
{
	int	result;

	result = 0;
	if (fd != -1)
		result = dup2(fd, fd2);
	return (result);
}
