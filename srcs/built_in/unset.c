/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:21:08 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 17:08:26 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "minishell.h"
#include <stdbool.h>

static void	ft_unset_declare_x(t_ctx *ctx, char *key)
{
	t_list			*prev;
	t_list			*current;
	t_dict_entry	*entry;

	prev = NULL;
	current = ctx->declare_x;
	while (current)
	{
		entry = current->content;
		if (ft_strcmp(key, entry->key) == 0)
		{
			if (!prev)
				ctx->declare_x = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, &ft_destroy_dict_entry);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

static void	ft_unset_env(t_ctx *ctx, char *key)
{
	t_list			*prev;
	t_list			*current;
	t_dict_entry	*entry;

	prev = NULL;
	current = ctx->env_dict;
	while (current)
	{
		entry = current->content;
		if (ft_strcmp(key, entry->key) == 0)
		{
			if (!prev)
				ctx->env_dict = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, &ft_destroy_dict_entry);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_unset(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	size_t	i;

	i = 1;
	while (i < argc)
	{
		ft_unset_env(ctx, argv[i]);
		ft_unset_declare_x(ctx, argv[i]);
		i++;
	}
	ft_free_double(&argv);
	if (is_child)
	{
		ft_destroy_ctx(ctx);
		exit(EXIT_SUCCESS);
	}
	ctx->last_error = EXIT_SUCCESS;
}
