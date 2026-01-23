/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:07:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 20:19:27 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

/*ctx_init*/
void	ft_env_init(t_ctx *ctx, char **env);
void	ft_init_ctx(t_ctx *ctx, int argc, char **env);

/*ctx_destroy*/
void	ft_destroy_ctx(t_ctx *ctx);
void	ft_clean_ctx(t_ctx *ctx);
void	ft_env_destroy(void *content);
void	ft_token_destoy(void *content);

#endif