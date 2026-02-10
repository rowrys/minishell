/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:07:20 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 11:39:53 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "minishell.h"

# include <stdbool.h>

/*ctx_destroy*/
void	ft_destroy_ctx(t_ctx *ctx);
void	ft_clean_ctx(t_ctx *ctx);
void	ft_destroy_dict_entry(void *content);
void	ft_token_destoy(void *content);

/*ctx_init*/
void	ft_init_ctx(t_ctx *ctx, int argc, char **argv, char **env);
void	ft_malloc_env_error(t_ctx *ctx, t_dict_entry *dict_entry,
			char **to_free);

/*env_init_default*/
char	**ft_env_default(void);

/*declare_x*/
void	ft_declare_x_init(t_ctx *ctx, char **tmp_env, bool free_42_angouleme);

#endif