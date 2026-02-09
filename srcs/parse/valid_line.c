/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:59:51 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:09:03 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "utils.h"

#include <stdbool.h>

static char	*ft_expand_vl(t_ctx *ctx, char *str, size_t size)
{
	char	*result;
	char	*name;

	if (!size || *str == '?')
	{
		if (!size)
			result = ft_strdup("$");
		else
			result = ft_itoa(ctx->last_error);
		if (!result)
			ft_free_and_error(str, ctx, MALLOC_ERROR, EXIT_FAILURE);
		return (result);
	}
	name = ft_substr(str, 0, size);
	if (!name)
		ft_free_and_error(str, ctx, MALLOC_ERROR, EXIT_FAILURE);
	result = ft_get_dict_value(ctx, ctx->env_dict, name);
	free(name);
	return (result);
}

static void	ft_insert_expand_vl(t_ctx *ctx, char **str, char **origin,
		char **result)
{
	char	*tmp;
	size_t	size;

	tmp = ft_substr(*origin, 0, *str - *origin);
	if (*origin != *str && !tmp)
	{
		free(*result);
		ft_free_and_error(*str, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	*result = ft_add_part(ctx, *result, tmp);
	size = ft_explen(*str + 1);
	tmp = ft_expand_vl(ctx, *str + 1, size);
	*result = ft_add_part(ctx, *result, tmp);
	*str += size + 1;
	*origin = *str;
}

static char	*ft_manage_expand_vl(t_ctx *ctx, char *str, bool skip_quote)
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
		if (skip_quote && (*str == '\'' || *str == '"'))
			str += ft_go_to(str + 1, *str) + 2;
		else if (*str == '$')
			ft_insert_expand_vl(ctx, &str, &origin, &result);
		else if (*str)
			str++;
	}
	if (str != origin || (skip_quote == false && to_free && !*to_free))
	{
		tmp = ft_get_part(ctx, origin, '\0');
		result = ft_add_part(ctx, result, tmp);
	}
	free(to_free);
	return (result);
}

bool	ft_is_empty(t_ctx *ctx, char *str)
{
	char	*line;
	int		i;

	line = ft_strdup(str);
	if (!line)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	line = ft_manage_expand_vl(ctx, line, 1);
	i = ft_skip(line, ISSPACE);
	if (line && line[i])
	{
		free(line);
		return (false);
	}
	free(line);
	return (true);
}

bool	ft_is_valid_line(t_ctx *ctx, char *str)
{
	bool	is_valid;

	is_valid = true;
	if (!*str)
		return (false);
	if (ft_is_syntax_error_quote(str))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token 'quote'",
			2);
		ctx->last_error = 2;
		is_valid = false;
	}
	if (is_valid && ft_is_empty(ctx, str))
		is_valid = false;
	return (is_valid);
}
