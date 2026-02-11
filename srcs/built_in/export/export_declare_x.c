/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:16:29 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 22:45:35 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"

#include <stdbool.h>
#include <stdlib.h>

static void	ft_declare_x_add_new_node(t_ctx *ctx, t_list *prev, t_list *current,
		t_list *new_node)
{
	void	*next_addr;

	if (!prev)
	{
		ctx->declare_x = new_node;
		new_node->next = current;
		return ;
	}
	next_addr = prev->next;
	prev->next = new_node;
	new_node->next = next_addr;
}

void	ft_replace_node_dict_entry(t_list *current, t_list *new_node)
{
	t_dict_entry	*new_dict_entry;
	t_dict_entry	*old_dict_entry;

	new_dict_entry = new_node->content;
	old_dict_entry = current->content;
	free(old_dict_entry->key);
	free(old_dict_entry->value);
	old_dict_entry->key = new_dict_entry->key;
	old_dict_entry->value = new_dict_entry->value;
	free(new_dict_entry);
	free(new_node);
}

static bool	ft_check_an_insert_entry(t_ctx *ctx, t_list *prev, t_list *current,
		t_list *new_node)
{
	t_dict_entry	*content;
	t_dict_entry	*dict_entry;
	int				cmp_key;

	dict_entry = new_node->content;
	content = current->content;
	cmp_key = ft_strcmp(dict_entry->key, content->key);
	if (cmp_key < 0)
	{
		ft_declare_x_add_new_node(ctx, prev, current, new_node);
		return (true);
	}
	else if (cmp_key == 0)
	{
		if (dict_entry->value)
			ft_replace_node_dict_entry(current, new_node);
		else
			ft_lstdelone(new_node, ft_destroy_dict_entry);
		return (true);
	}
	return (false);
}

void	ft_put_in_declare_x(t_ctx *ctx, t_list *new_node)
{
	t_list	*current;
	t_list	*prev;

	prev = NULL;
	current = ctx->declare_x;
	while (current)
	{
		if (ft_check_an_insert_entry(ctx, prev, current, new_node))
			return ;
		prev = current;
		current = current->next;
	}
	prev->next = new_node;
}
