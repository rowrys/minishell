/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:20:36 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/09 09:10:54 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>

static bool	ft_have_sep(char **exp_split, char *exp, size_t block)
{
	if (exp_split[block])
		return (true);
	if (!exp_split[block] && ft_strchr(ISSPACE, exp[ft_strlen(exp) - 1]))
		return (true);
	return (false);
}

static bool	ft_add_split_expand(t_ctx *ctx, t_list **new_list, t_token *token,
		char **result)
{
	char	**exp_splt;
	char	*exp;
	size_t	block;

	block = -1;
	exp = ft_expand(ctx, token->value + 1, ft_explen(token->value + 1));
	exp_splt = ft_split_expand(ctx, exp);
	if (ft_is_redir_key(token->type) && *exp_splt && *(exp_splt + 1))
	{
		ft_add_token(ctx, new_list, token->type, NULL);
		free(exp);
		ft_free_double(&exp_splt);
		return (true);
	}
	while (exp_splt[++block])
	{
		*result = ft_add_part(ctx, *result, exp_splt[block]);
		if (ft_have_sep(exp_splt, exp, block + 1))
			ft_add_token(ctx, new_list, token->type, *result);
		if (ft_have_sep(exp_splt, exp, block + 1))
			*result = NULL;
	}
	free(exp);
	free(exp_splt);
	return (false);
}

bool	ft_parse_expand(t_ctx *ctx, t_list **new_list, t_token *token,
		char **result)
{
	char	*exp;
	bool	is_ambigous;

	is_ambigous = false;
	exp = ft_expand(ctx, token->value + 1, ft_explen(token->value + 1));
	if (ft_is_redir_key(token->type) && !exp)
	{
		ft_add_token(ctx, new_list, token->type, NULL);
		return (true);
	}
	if (exp && ft_is_inside_quote(exp))
	{
		*result = ft_add_part(ctx, *result, exp);
		return (is_ambigous);
	}
	if (exp && ft_strchr(ISSPACE, *exp) && *result)
	{
		ft_add_token(ctx, new_list, token->type, *result);
		*result = NULL;
	}
	if (exp && ft_add_split_expand(ctx, new_list, token, result))
		is_ambigous = true;
	free(exp);
	return (is_ambigous);
}

void	ft_parse_block(t_ctx *ctx, t_token *token, char **result)
{
	char	*part;
	size_t	size;

	size = 0;
	while (!ft_strchr(PART_LIMITER, token->value[size]))
		size++;
	part = ft_substr(token->value, 0, size);
	if (!part)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	*result = ft_add_part(ctx, *result, part);
	token->value += size;
}

void	ft_parse_quote(t_ctx *ctx, t_token *token, char **result)
{
	char	*part;

	part = ft_get_part(ctx, token->value + 1, *token->value);
	if (*token->value == '"')
		part = ft_manage_expand(ctx, part, 0);
	*result = ft_add_part(ctx, *result, part);
	token->value += ft_go_to(token->value + 1, *token->value) + 2;
}
