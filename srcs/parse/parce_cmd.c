/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:50:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/23 14:06:47 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ctx.h"
#include "minishell.h"
#include "parse.h"

void	parse_cmd(t_ctx *ctx)
{
	t_list	*old_lst_token;
	t_cmd	*current_cmd;
	t_list	*lst;
	
	lst = ctx->cmd_lst;
	while (lst)
	{
		current_cmd = lst->content;
		old_lst_token = current_cmd->token;
		current_cmd->token = ft_parse_token_list(ctx, old_lst_token);
		ft_lstclear(&old_lst_token, &ft_token_destoy);
		lst = lst->next;
	}
}
