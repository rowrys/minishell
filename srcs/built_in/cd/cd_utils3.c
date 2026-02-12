/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:18:44 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/12 13:16:18 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>

static t_list	*ft_new_entry(t_ctx *ctx, char *key, char *value,
		char **free_42)
{
	t_list			*new_node;
	t_dict_entry	*entry;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		ft_free_db_and_error(free_42, ctx, MALLOC_ERROR, EXIT_FAILURE);
	entry = ft_calloc(1, sizeof(t_dict_entry));
	if (!entry)
		ft_lst_db_str_malloc(ctx, new_node, free_42, NULL);
	new_node->content = entry;
	entry->key = ft_strdup(key);
	if (!entry->key)
		ft_lst_db_str_malloc(ctx, new_node, free_42, NULL);
	entry->value = ft_strdup(value);
	if (!entry->value && value)
		ft_lst_db_str_malloc(ctx, new_node, free_42, NULL);
	return (new_node);
}

void	ft_repl_entry_value(t_ctx *ctx, char *key, char *value, char **free_42)
{
	t_list			*env_dict;
	t_list			*new_node;
	t_dict_entry	*entry;

	env_dict = ctx->env_dict;
	new_node = ft_new_entry(ctx, key, value, free_42);
	ft_put_in_declare_x(ctx, new_node);
	while (env_dict)
	{
		entry = env_dict->content;
		if (!ft_strcmp(entry->key, key))
		{
			free(entry->value);
			entry->value = value;
			return ;
		}
		env_dict = env_dict->next;
	}
	if (!value)
		return ;
	new_node = ft_new_entry(ctx, key, value, free_42);
	free(value);
	ft_put_in_env(ctx, new_node);
}
