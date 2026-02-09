/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:15:17 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 08:47:37 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "execute.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>

static char	**ft_envdup(t_ctx *ctx, char **env, size_t size)
{
	char	**result;
	size_t	i;

	result = ft_calloc(size + 1, sizeof(char *));
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		result[i] = ft_strdup(env[i]);
		if (!result[i])
			ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
		i++;
	}
	return (result);
}

static char	*ft_get_next(t_ctx *ctx, char **env, int size, char **dx)
{
	int		current;
	int		next;
	char	*result;

	current = 0;
	next = -1;
	while (current < size)
	{
		if (next == -1 && env[current])
			next = current;
		if (env[current] && ft_strcmp(env[current], env[next]) < 0)
			next = current;
		current++;
	}
	result = ft_strdup(env[next]);
	if (!result)
	{
		ft_free_double(&dx);
		ft_free_db_and_error(env, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	free(env[next]);
	env[next] = NULL;
	return (result);
}

static char	**ft_sort_env(t_ctx *ctx, char **tmp_env, bool free_42_angouleme)
{
	char	**result;
	char	**env;
	size_t	size;
	size_t	i;

	size = ft_get_argc(tmp_env);
	env = tmp_env;
	if (free_42_angouleme == false)
		env = ft_envdup(ctx, tmp_env, size);
	result = ft_calloc(size + 1, sizeof(char *));
	if (!result)
		ft_free_db_and_error(env, ctx, MALLOC_ERROR, EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		result[i] = ft_get_next(ctx, env, size, result);
		i++;
	}
	free(env);
	return (result);
}

static t_dict_entry	*ft_declare_x_entry(t_ctx *ctx, char **free_42, char *env)
{
	size_t			i;
	t_dict_entry	*new_dict_entry;

	new_dict_entry = NULL;
	i = 0;
	if (!*env)
		return (NULL);
	i = ft_go_to(env, '=');
	new_dict_entry = ft_calloc(1, sizeof(t_dict_entry));
	if (!new_dict_entry)
		ft_free_db_and_error(free_42, ctx, MALLOC_ERROR, EXIT_FAILURE);
	new_dict_entry->key = ft_substr(env, 0, i);
	if (!new_dict_entry->key)
		ft_malloc_env_error(ctx, new_dict_entry, free_42);
	if (ft_strchr(env, '='))
		new_dict_entry->value = ft_strdup(env + i + 1);
	if (ft_strchr(env, '=') && env[i + 1] && !new_dict_entry->value)
		ft_malloc_env_error(ctx, new_dict_entry, free_42);
	return (new_dict_entry);
}

void	ft_declare_x_init(t_ctx *ctx, char **tmp_env, bool free_42_angouleme)
{
	size_t			i;
	t_list			*new_node;
	t_dict_entry	*declare_x_entry;
	char			**env;

	ctx->declare_x = NULL;
	i = 0;
	env = ft_sort_env(ctx, tmp_env, free_42_angouleme);
	while (env[i])
	{
		declare_x_entry = ft_declare_x_entry(ctx, env, env[i]);
		if (declare_x_entry)
		{
			new_node = ft_lstnew(declare_x_entry);
			if (!new_node)
				ft_free_db_and_error(env, ctx, MALLOC_ERROR, EXIT_FAILURE);
			ft_lstadd_back(&ctx->declare_x, new_node);
		}
		i++;
	}
	ft_free_double(&env);
}
