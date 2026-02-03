/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:58:15 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 19:24:15 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <string.h>

static char	*ft_triple_join(t_ctx *ctx, char *key, char *sep, char *value)
{
	char	*result;
	char	*tmp;
	
	result = strdup(key);
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	tmp = ft_strjoin(result, sep);
	free(result);
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	result = ft_strjoin(tmp, value);
	free(tmp);
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	return (result);
}

char	**ft_env_to_array(t_ctx *ctx, t_list *env_dict)
{
	t_list			*env_list;
	t_dict_entry	*entry;
	char 			**result;
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