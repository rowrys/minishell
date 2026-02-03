/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:23:07 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/03 15:17:56 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	ft_close(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void	ft_replace_fd(int *old_fd, int new_fd)
{
	ft_close(old_fd);
	*old_fd = new_fd;
}

void ft_close_cmd_fds(t_cmd *cmd)
{
    ft_close(&cmd->fd_in);
    ft_close(&cmd->fd_out);
    ft_close(&cmd->pipe_cmd[0]);
    ft_close(&cmd->pipe_cmd[1]);
    ft_close(&cmd->pipe_hd[0]);
    ft_close(&cmd->pipe_hd[1]);
}
