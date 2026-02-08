/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:13:52 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/08 18:43:39 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"
#include "built_in.h"
#include "utils.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static void	ft_put_in_env(t_ctx *ctx, char **argv, t_dict_entry *dict_entry)
{
	t_dict_entry	*current_dict_entry;
	t_list			*current_node;
	t_list			*new_node;

	current_node = ctx->env_dict;
	while (current_node)
	{
		current_dict_entry = current_node->content;
		if (!ft_strcmp(dict_entry->key, current_dict_entry->key))
		{
			free(current_dict_entry->key);
			current_dict_entry->key = dict_entry->key;
			free(current_dict_entry->value);
			current_dict_entry->value = dict_entry->value;
			free(dict_entry);
			return ;
		}
		current_node = current_node->next;
	}
	new_node = ft_lstnew(dict_entry);
	if (!new_node)
	{
		free(dict_entry->key);
		free(dict_entry->value);
		free(dict_entry);
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	ft_lstadd_back(&ctx->env_dict, new_node);
}

void	ft_add_to_list(t_ctx *ctx, char **argv, char *str)
{
	char			*key;
	char			*value;
	t_dict_entry	*dict_entry;

	key = ft_get_key(ctx, argv, str);
	value = ft_get_value(ctx, argv, str, key);
	dict_entry = malloc(sizeof(t_dict_entry));
	if (!dict_entry)
	{
		free(value);
		free(key);
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);		
	}
	dict_entry->key = key;
	dict_entry->value = value;
	// ft_put_in_declar_x();
	if (dict_entry->value)
		ft_put_in_env(ctx, argv, dict_entry);
}

static void	ft_export_display_declar_x(t_ctx *ctx, bool is_clone, char **free_42_angouleme)
{
    t_list          *env_dict;
    t_dict_entry    *entry;
	char			*result;

	ft_free_double(&free_42_angouleme);
    env_dict = ctx->declare_x;
    while (env_dict)
    {
        entry = env_dict->content;
		result = ft_triple_join(ctx, entry->key, "=", entry->value);
		ft_putendl_fd(result, 1);
		free(result);
        env_dict = env_dict->next;
    }
    if (is_clone)
    {
        ft_destroy_ctx(ctx);
        exit(EXIT_SUCCESS);
    }
    ctx->last_error = EXIT_SUCCESS;
}

void	ft_export(t_ctx *ctx, bool is_clone, size_t argc, char **argv)
{
	bool	exit_code;
	size_t	i;

	if (argc == 1)
		ft_export_display_declar_x(ctx, is_clone, argv);
	if (argc == 1)
		return ;
	exit_code = 0;
	i = 1;
	while (argc != 1 && argv[i])
	{
		if (!ft_is_valid_identifier(argv[i]))
			exit_code = 1;
		else
			ft_add_to_list(ctx, argv, argv[i]);
		i++;
	}
	ft_free_double(&argv);
	if (is_clone)
	{
		ft_destroy_ctx(ctx);
		exit(exit_code);
	}
	ctx->last_error = exit_code;
}
