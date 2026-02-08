/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/08 17:32:43 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_destroy_dict_entry(void *content)
{
	const t_dict_entry	*temp = content;
	
	if (!content)
		return ;
	free(temp->key);
	free(temp->value);
	free(content);	
}

void	ft_token_destoy(void *token)
{
	char	*value;

	value = ((t_token *)(token))->value;
	free(value);
	free(token);
}

static void	ft_cmd_destroy(void *cmd)
{
	t_list	*token_lst;

	ft_close_cmd_fds(cmd);
	token_lst = ((t_cmd *)(cmd))->token;
	if (token_lst)
		ft_lstclear(&token_lst, &ft_token_destoy);
	free(cmd);
}

void	ft_clean_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	free(ctx->line);
	ctx->line = NULL;
	ft_close(&ctx->stdin_fileno);
	ft_close(&ctx->stdout_fileno);
	if (ctx->cmd_lst)
		ft_lstclear(&ctx->cmd_lst, &ft_cmd_destroy);	
	ctx->cmd_lst = NULL;
}

void	ft_destroy_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	ft_clean_ctx(ctx);
	if (ctx->line_split)
		ft_free_double(&ctx->line_split);
	ctx->line_split = NULL;
	ft_lstclear(&ctx->env_dict, &ft_destroy_dict_entry);
	ft_lstclear(&ctx->declare_x, &ft_destroy_dict_entry);
	ctx->env_dict = NULL;		
}
