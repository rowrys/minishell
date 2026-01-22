/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 10:31:02 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "utils.h"

void	ft_env_init(t_ctx *ctx, char **env)
{
	size_t			i;
	size_t			j;
	t_dict_entry	*content;
	
	ctx->env_dict = NULL;
	i = 0;
	while (env[i])
	{
		content = malloc(sizeof(t_dict_entry));
		// if (!ctx->env_dict->content)
		// 	ft_error(ctx, "malloc error", 1);
		ft_bzero(content, sizeof(t_dict_entry));
		j = ft_go_to(env[i], '=');
		if (env[i][j] != '\0')
		{
			content->key = ft_substr(env[i], 0, j);
			// if (!ctx->env_dict->content)
			// 	ft_error(ctx, "malloc error", 1);
			content->value = ft_strdup(ft_strchr(env[i], '=') + 1);
			// if (!ctx->env_dict->content)
			// 	ft_error(ctx, "malloc error", 1);
			ft_lstadd_back(&ctx->env_dict, ft_lstnew(content));
		}
		i++;
	}
}

void	ft_init_ctx(t_ctx *ctx, int argc, char **env)
{
	// if (argc != 1)
(void)argc;
	// 	ft_error(NULL, "format: ./minishell: do not add arguments", 1);
	ft_bzero(ctx, sizeof(t_ctx));
	ft_env_init(ctx, env);
}
