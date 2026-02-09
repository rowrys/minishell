/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:58:15 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:20:14 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <string.h>

char	**ft_env_to_array(t_ctx *ctx, t_list *env_dict)
{
	t_list			*env_list;
	t_dict_entry	*entry;
	char			**result;
	size_t			i;

	env_list = ctx->env_dict;
	i = ft_lstsize(env_list);
	result = ft_calloc(i + 1, sizeof(char *));
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	env_dict = ctx->env_dict;
	i = 0;
	while (env_dict)
	{
		entry = env_dict->content;
		result[i] = ft_triple_join(ctx, entry->key, "=", entry->value);
		i++;
		env_dict = env_dict->next;
	}
	return (result);
}

void	ft_replace_entry_value(t_ctx *ctx, char *key, char *new_ptr)
{
	t_list			*env_dict;
	t_dict_entry	*entry;

	env_dict = ctx->env_dict;
	while (env_dict)
	{
		entry = env_dict->content;
		if (!ft_strcmp(entry->key, key))
		{
			entry->value = new_ptr;
			break ;
		}
		env_dict = env_dict->next;
	}
}

char	*ft_get_entry_ptr(t_ctx *ctx, char *key)
{
	t_list			*env_dict;
	t_dict_entry	*entry;
	char			*cd_path;

	env_dict = ctx->env_dict;
	cd_path = NULL;
	while (env_dict)
	{
		entry = env_dict->content;
		if (!ft_strcmp(entry->key, key))
		{
			cd_path = entry->value;
			break ;
		}
		env_dict = env_dict->next;
	}
	return (cd_path);
}

char	*ft_get_dict_value(t_ctx *ctx, t_list *tmp_dict, char *name)
{
	char			*result;
	t_dict_entry	*entry;

	result = NULL;
	while (tmp_dict)
	{
		entry = tmp_dict->content;
		if (!ft_strcmp(entry->key, name))
		{
			result = ft_strdup(entry->value);
			if (!result && entry->value)
			{
				free(name);
				ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
			}
			break ;
		}
		tmp_dict = tmp_dict->next;
	}
	return (result);
}
