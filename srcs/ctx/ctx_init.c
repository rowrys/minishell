/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 13:54:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 11:39:28 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_malloc_env_error(t_ctx *ctx, t_dict_entry *dict_entry,
		char **to_free)
{
	if (dict_entry)
		ft_destroy_dict_entry(dict_entry);
	if (to_free)
		ft_free_double(&to_free);
	ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
}

static t_dict_entry	*ft_init_new_dict_entry(t_ctx *ctx, char *env)
{
	size_t			i;
	t_dict_entry	*new_dict_entry;

	new_dict_entry = NULL;
	i = 0;
	if (!*env)
		return (NULL);
	i = ft_go_to(env, '=');
	new_dict_entry = ft_calloc(sizeof(t_dict_entry), 1);
	if (!new_dict_entry)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	new_dict_entry->key = ft_substr(env, 0, i);
	if (!new_dict_entry->key)
		ft_malloc_env_error(ctx, new_dict_entry, NULL);
	if (ft_strchr(env, '='))
		new_dict_entry->value = ft_strdup(ft_strchr(env, '=') + 1);
	if (ft_strchr(env, '=') && !new_dict_entry->value)
		ft_malloc_env_error(ctx, new_dict_entry, NULL);
	return (new_dict_entry);
}

static void	ft_env_init(t_ctx *ctx, char **env)
{
	size_t			i;
	t_list			*new_node;
	t_dict_entry	*new_dict_entry;

	ctx->env_dict = NULL;
	i = 0;
	while (env[i])
	{
		new_dict_entry = ft_init_new_dict_entry(ctx, env[i]);
		if (new_dict_entry)
		{
			new_node = ft_lstnew(new_dict_entry);
			if (!new_node)
				ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
			ft_lstadd_back(&ctx->env_dict, new_node);
		}
		i++;
	}
}

void	ft_init_ctx(t_ctx *ctx, int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
		ft_error(NULL, "format: ./minishell: do not add arguments", 2);
	ft_bzero(ctx, sizeof(t_ctx));
	ctx->stdin_fileno = -1;
	ctx->stdout_fileno = -1;
	if (!*env)
	{
		env = ft_env_default();
		ft_env_init(ctx, env);
		ft_declare_x_init(ctx, env, true);
	}
	else
	{
		ft_env_init(ctx, env);
		ft_declare_x_init(ctx, env, false);
	}
}
