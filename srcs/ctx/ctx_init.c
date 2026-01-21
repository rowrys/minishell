/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/21 14:01:53 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_ctx(t_ctx *ctx, int argc, char **env)
{
	// if (argc != 1)
		// ft_error(NULL, "format: ./minishell: do not add arguments", 1);
	ft_bzero(ctx, sizeof(t_ctx));
	// init ctx->env_dict
}

void	env_init(t_ctx *ctx, char **env)
{
	size_t			i;
	t_dict_entry	*content;
	
	(void)ctx;
	i = 0;
	while (env[i])
	{
		content = malloc(sizeof(t_dict_entry));
		// if (!ctx->env_dict->content)
		// 	ft_error(ctx, "malloc error", 1);
		content->key = ft_strchr(env[i], '=');
		printf("%s", content->key);
		// ft_lstadd_back(ctx->env_dict->content, ft_lstnew(content));		
		i++;
	}
}