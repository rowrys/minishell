/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_chunk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:36:41 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/05 15:16:52 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "utils.h"

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

static bool	ft_is_reg(char *bin)
{
	struct stat bin_stat;
	
	if (stat(bin, &bin_stat) == 0 && S_ISREG(bin_stat.st_mode))
			return (true);
	return (false);
}


static bool	ft_is_dir(char *bin)
{
	struct stat bin_stat;
	
	if (stat(bin, &bin_stat) == 0 && S_ISDIR(bin_stat.st_mode))
		return (true);
	return (false);
}

static char    **ft_get_path_split(t_ctx *ctx)
{
	t_list			*env_dict;
	t_dict_entry	*entry;
	char			**result;
	char			*temp;

	env_dict = ctx->env_dict;
	temp = NULL;
	while (env_dict)
	{
		entry = env_dict->content;
		if (!ft_strcmp(entry->key, "PATH"))
		{
			temp = entry->value;
			break ;
		}
		env_dict = env_dict->next;
	}
	if (!temp || !*temp)
		return (NULL);
	result = ft_split(temp, ':');
	if(!result)
		ft_error(ctx, "Malloc exploded, how did you do that???", EXIT_FAILURE);
	return (result);
}

static char	*ft_check_bin_denied_42_angouleme(t_ctx *ctx, char **splited_path, size_t i,
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
	if (bin && access(bin,F_OK) == 0 && !ft_is_dir(bin) && ft_is_reg(bin))
			return (bin);
	free(bin);
	return (NULL);
}

static char	*ft_check_bin_42_angouleme(t_ctx *ctx, char **splited_path, size_t i,
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
	if (bin && access(bin,X_OK) == 0 && ft_is_reg(bin) && !ft_is_dir(bin))
			return (bin);
	free(bin);
	return (NULL);
}

static char    *ft_get_bin_path(t_ctx *ctx, char **splited_path, char *binary, char **env)
{
    char    *bin;
	char	*bin_denied;
    size_t	i;

	i = 0;
	bin = NULL;
	bin_denied = NULL;
	while (splited_path[i] && !bin)
    {
		bin = ft_check_bin_42_angouleme(ctx, splited_path, i, binary);
		if (!bin_denied)
			bin_denied = ft_check_bin_denied_42_angouleme(ctx,
				splited_path, i, binary);
		i++;
	}
	if (!bin && bin_denied)
		return (bin_denied);
	free(bin_denied);
	if (!ft_is_reg(bin) || ft_is_dir(bin))
	{
		free(bin);
		ft_free_double(&splited_path);
		ft_cmd_not_found(ctx, binary, env);
	}
	return (bin);
}

static char	*ft_get_bin(t_ctx *ctx, char *binary, char **env)
{
	char	*result;
	char	**splited_path;

	splited_path = ft_get_path_split(ctx);
	if (!splited_path)
		return (binary);
	result = ft_get_bin_path(ctx, splited_path, binary, env);
	ft_free_double(&splited_path);
	if (!result)
		ft_cmd_not_found(ctx, binary, env);
	return (result);
}

static char	*ft_is_valid_binary(t_ctx *ctx, char *binary, char **env)
{
    char    *result;
	bool	is_dir;
	bool	is_reg;

	is_dir = ft_is_dir(binary);
	is_reg = ft_is_reg(binary);
	if (is_dir)
	{
		ft_free_double(&env);
		result = ft_strdup(binary);
		if (!result)
			ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
		ft_error_execve(ctx, result,  EISDIR);		
	}
	else if (!access(binary, X_OK) && !is_dir && is_reg)
		return (binary);
	else if (ft_strchr(binary, '/'))
		return (binary);
	// else if (!*binary)
	// 	ft_cmd_not_found(ctx, binary, env);
	result = ft_get_bin(ctx, binary, env);
	return (result);
}

static int	ft_dup(int fd, int fd2)
{
	int	result;
	
	result = 0;
	if (fd != -1)
		result = dup2(fd, fd2);
	return (result);
}

void ft_execute_chunk(t_ctx *ctx, t_cmd *cmd, char *binary)
{
	char	**args;
	char	**env;
	char	*path_binary;
	int		errno_tmp;

	ft_manage_redir(ctx, cmd, REDIR_FORKED);
	env = ft_env_to_array(ctx, ctx->env_dict);
	path_binary = ft_is_valid_binary(ctx, binary, env);
	if (ft_dup(cmd->fd_in, STDIN_FILENO) == -1)
		ft_free_db_and_error(env, ctx, "dup2: ", EXIT_FAILURE);
	if (ft_dup(cmd->fd_out, STDOUT_FILENO) == -1)
		ft_free_db_and_error(env, ctx, "dup2: ", EXIT_FAILURE);		
	args = ft_cmd_to_arg(ctx, cmd);
	ft_close_cmd_fds(cmd);
	execve(path_binary, args, env);
	errno_tmp = errno;
	ft_free_double(&args);
	ft_free_double(&env);
	if (path_binary == binary)
		path_binary = ft_strdup(binary);
	if (!path_binary)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_error_execve(ctx, path_binary, errno_tmp);
}
