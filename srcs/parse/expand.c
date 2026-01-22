/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:15:49 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 14:47:02 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

char	*ft_expand(t_ctx *ctx, char *str, size_t size)
{
	char	*result;
	char	*name;

	if (!size)
	{
		result = ft_strdup("$");
		return (result);
	}
	if (!ft_strcmp(str, "?"))
	{
		result = ft_itoa(ctx->last_error);
		// if (!result)
		// 	ft_error(ctx, "malloc error", 1);
		return (result);
	}
	name = ft_substr(str, 0, size);
	// if (name)
	// 	ft_error()
	result = ft_get_dict_value(ctx, ctx->env_dict, name);
	free(name);
	return (result);
}

size_t	ft_explen(char *str)
{
	size_t size;

	if (!str)
		return (0);
	size = 0;
	while (str[size] && !ft_strchr(EXPAND_LIMITER, str[size]))
		size++;
	return (size);
}

static void	ft_insert_expand(t_ctx *ctx, char **str, char **new_origin, char **result)
{
	char	*tmp;
	size_t	size;

	tmp = ft_get_part(ctx, *new_origin, '$');
	*result = ft_add_part(ctx, *result, tmp);
	size = ft_explen(*str + 1);
	tmp = ft_expand(ctx, *str + 1, size);
	*result = ft_add_part(ctx, *result, tmp);
	*str += size;
	*new_origin = *str + 1;
}

char	*ft_manage_expand(t_ctx *ctx, char *str, bool skip_quote)
{
	char	*result;
	char	*tmp;
	char	*origin;
	char	*to_free;

	origin = str;
	to_free = str;
	result = NULL;
	while (str && *str)
	{
		printf("%s\n", str);
		if (skip_quote && (*str == '\'' || *str == '"'))
			str = ft_strchr(str + 1, *str);
		else if (*str == '$')
			ft_insert_expand(ctx, &str, &origin, &result);
		if (*str)
			str++;
	}
	if (str != origin)
	{
		tmp = ft_get_part(ctx, origin, '\0');
		result = ft_add_part(ctx, result, tmp);
	}
	free(to_free);
	return (result);
}
