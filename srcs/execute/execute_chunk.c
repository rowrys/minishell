/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_chunk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:36:41 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/04 09:49:07 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "execute.h"
#include "utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

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

static char    *ft_get_bin_path(t_ctx *ctx, char **splited_path, char *binary, bool *have_access_denied)
{
    char    *path_part;
    char    *bin;
    int        i;

    bin = NULL;
	i = 0;
    while (splited_path[i])
    {
        path_part = ft_strjoin(splited_path[i], "/");
		if (!path_part)
			ft_free_and_error(splited_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
		bin = ft_strjoin(path_part, binary);
		free(path_part);
		if (!bin)
			ft_free_and_error(splited_path, ctx, MALLOC_ERROR, EXIT_FAILURE);
        if (bin && access(bin,X_OK) == 0)
			return (bin);
		if (bin && access(bin, F_OK) == 0)
			*have_access_denied = true;
		free(bin);
        bin = NULL;
		i++;
	}
    return (bin);
}

static char	*ft_get_bin(t_ctx *ctx, char *binary, char **env)
{
	bool	have_access_denied;
	char	*result;
	char	**splited_path;

	splited_path = ft_get_path_split(ctx);
	if (!splited_path)
		ft_cmd_not_found(ctx, binary, env);
	have_access_denied = false;
	result = ft_get_bin_path(ctx, splited_path, binary, &have_access_denied);
	if (!result && have_access_denied)
		ft_access_denied(ctx, splited_path, binary, env);
	else if (!result)
	{
		ft_cmd_not_found(ctx, binary, env);
		ft_free_double(&splited_path);
		ft_free_double(&env);
		free(result);
		ft_destroy_ctx(ctx);
		exit(EXIT_CMD_NOT_FOUND);
	}
	else
		ft_free_double(&splited_path);
	return (result);
}

static char	*ft_is_valid_binary(t_ctx *ctx, char *binary, char **env)
{
    char    *result;
    int        fd_temp;

    fd_temp = open(binary, O_RDWR);
    if (fd_temp < 0 && errno == EISDIR)
        ft_free_and_error(env, ctx, binary, EXIT_FAILURE);
    else
        close(fd_temp);
    if (access(binary, F_OK) == 0)
    {
        if (access(binary, X_OK) == 0)
            return (binary);
        else
            ft_access_denied(ctx, NULL, binary, env);
    }
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

	ft_manage_redir(ctx, cmd, REDIR_FORKED);
	env = ft_env_to_array(ctx, ctx->env_dict);
	path_binary = ft_is_valid_binary(ctx, binary, env);
	if (ft_dup(cmd->fd_in, STDIN_FILENO) == -1)
	{
		ft_free_double(&env);
		ft_error(ctx, "dup2: ", EXIT_FAILURE);
	}
	if (ft_dup(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		ft_free_double(&env);
		ft_error(ctx, "dup2: ", EXIT_FAILURE);		
	}
	args = ft_cmd_to_arg(ctx, cmd);
	ft_close_cmd_fds(cmd);
	execve(path_binary, args, env);
	ft_free_double(&args);
	ft_free_double(&env);
	free(path_binary);
	ft_error(ctx, "execve: ", EXIT_FAILURE);	
}
