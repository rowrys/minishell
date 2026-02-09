/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:07:23 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:08:55 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "minishell.h"
#include "parse.h"

static void	ft_parse_cmd(t_ctx *ctx)
{
	t_list	*new_token_list;
	t_list	*old_token_list;
	t_cmd	*current_cmd;
	t_list	*cmd_lst;

	cmd_lst = ctx->cmd_lst;
	while (cmd_lst)
	{
		current_cmd = cmd_lst->content;
		old_token_list = current_cmd->token;
		new_token_list = ft_parse_token_list(ctx, old_token_list);
		ft_lstclear(&old_token_list, &ft_token_destoy);
		current_cmd->token = new_token_list;
		cmd_lst = cmd_lst->next;
	}
}

void	ft_parse(t_ctx *ctx)
{
	ft_parse_line(ctx);
	ft_parse_cmd(ctx);
}
