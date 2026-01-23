/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:44:53 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/23 18:25:12 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ctx.h"
#include "minishell.h"
#include "parse.h"

void	ft_parse_cmd(t_ctx *ctx)
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
