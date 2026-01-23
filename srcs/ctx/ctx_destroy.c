/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/23 11:27:00 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_env_destroy(void *content)
{
	if (!content)
		return ;
	free(((t_dict_entry *)(content))->key);
	((t_dict_entry *)(content))->key = NULL;
	free(((t_dict_entry *)(content))->value);
	((t_dict_entry *)(content))->value = NULL;
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
	if (ctx->cmd_lst)
		ft_lstclear(&ctx->cmd_lst, &ft_cmd_destroy);	
	ctx->cmd_lst = NULL;
}

void	ft_destroy_ctx(t_ctx *ctx)
{
	if (!ctx)
		return ;
	ft_clean_ctx(ctx);
	if (ctx->env_dict)
		ft_lstclear(&ctx->env_dict, &ft_env_destroy);
	ctx->env_dict = NULL;		
}
