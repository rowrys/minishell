/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:13:52 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 16:52:12 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"
#include "built_in.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static void	ft_put_in_env(t_ctx *ctx, t_list *new_node)
{
	t_dict_entry	*current_dict_entry;
	t_list			*current_node;
	t_dict_entry	*dict_entry;

	dict_entry = new_node->content;
	current_node = ctx->env_dict;
	while (current_node)
	{
		current_dict_entry = current_node->content;
		if (!ft_strcmp(dict_entry->key, current_dict_entry->key))
		{
			ft_replace_node_dict_entry(current_node, new_node);
			return ;
		}
		current_node = current_node->next;
	}
	ft_lstadd_back(&ctx->env_dict, new_node);
}

static void	ft_add_to_list(t_ctx *ctx, char **argv, char *str)
{
	t_list	*new_node;
	bool	have_value;

	(void)argv;
	have_value = false;
	new_node = ft_creat_lst_dict_entry(ctx, argv, str);
	if (((t_dict_entry *)new_node->content)->value)
		have_value = true;
	ft_put_in_declare_x(ctx, new_node);
	if (have_value)
	{
		new_node = ft_creat_lst_dict_entry(ctx, argv, str);
		ft_put_in_env(ctx, new_node);
	}
}

static void	ft_export_display_declar_x(t_ctx *ctx, bool is_clone, char **free_42_angouleme)
{
    t_list          *env_dict;
    t_dict_entry    *entry;

	ft_free_double(&free_42_angouleme);
    env_dict = ctx->declare_x;
    while (env_dict)
    {
        entry = env_dict->content;
    	ft_putstr_fd("declare ", 1);
    	ft_putstr_fd(entry->key, 1);
    	ft_putstr_fd("=", 1);
    	ft_putstr_fd("\"", 1);
    	ft_putstr_fd(entry->value, 1);
    	ft_putendl_fd("\"", 1);
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
