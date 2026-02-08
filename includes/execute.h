/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 10:48:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/08 15:24:43 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

# include <stdbool.h>

# define REDIR_BUILT_IN 1
# define REDIR_FORGOTTEN -1
# define REDIR_FORKED 0

/*execute*/
void    ft_execute(t_ctx *ctx);
int		ft_check_status(int status);

/*execute_cmd*/
void	ft_execute_cmd(t_ctx *ctx, t_cmd *cmd);

/*execute_chunk*/
void ft_execute_chunk(t_ctx *ctx, t_cmd *cmd, char *binary);

/*execute_built_in*/
void	ft_execute_built_in(t_ctx *ctx, t_cmd *cmd, t_built_in built_in_type);
size_t	ft_get_argc(char **argv);

/*forgotten_child*/
void	ft_forgotten_child(t_ctx *ctx, t_cmd *cmd);

/*manage_redir*/
void	ft_manage_redir(t_ctx *ctx, t_cmd *cmd, int mode);

/*cmd_to_arg*/
char	**ft_cmd_to_arg(t_ctx *ctx, t_cmd *cmd);

#endif