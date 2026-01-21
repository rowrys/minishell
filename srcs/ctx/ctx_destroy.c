/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/21 14:03:51 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_destroy_ctx(t_ctx *ctx)
{

}

void	ft_clean_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	free(ctx->line);
	if (ctx->cmd_lst)
		ft_lstclear(&ctx->cmd_lst, &ft_clean_cmd_lst);
}