/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:58:18 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 13:26:33 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"
#include "execute.h"
#include <stddef.h>

static int	ft_built_in(t_ctx *ctx, t_cmd *cmd, t_built_in built_in_type)
{
	int		status;
	char	**args;
	static int		(*built_in_fonction[])(t_ctx *, char**) = {&ft_echo, &ft_cd, &ft_pwd,
										&ft_export, &ft_unset, &ft_env, &ft_exit}

	args = ft_cmd_to_arg(cmd);
	// quid de stdin et stdout dans les built in
	status = built_in_fonction[built_in_type - 1](ctx, args);
	ft_free_double(&args);
	return (status);
}

void	ft_execute_built_in(t_ctx *ctx, t_cmd *cmd, t_built_in built_in_type)
{
	int status;

	ft_manage_redir(ctx, cmd, )
	{	
		ctx->last_error = 1;
		return ;
	}
	status = ft_built_in(ctx, cmd, built_in_type);
	if (cmd->cpid != -2)
	{
		ft_destroy_ctx(ctx);
		exit(status);
	}
	else
		ctx->last_error = status;
}
