/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:22:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 10:16:42 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

int	ft_get_redir_key(char *str)
{
	if (!ft_strncmp(str, "<<", 2) && !ft_strchr("<>", str[2]))
		return (KEY_HERE_DOC);
	if (!ft_strncmp(str, ">>", 2) && !ft_strchr("<>", str[2]))
		return (KEY_APPEND);
	if (!ft_strncmp(str, "<", 1) && !ft_strchr("<>", str[1]))
		return (KEY_LREDIR);
	if (!ft_strncmp(str, ">", 1) && !ft_strchr("<>", str[1]))
		return (KEY_RREDIR);
	return (0);
}

void	ft_add_token(t_ctx *ctx, t_list **token_lst, int key, char *value)
{
	t_token	*new_token;
	t_list	*new_entry;

	new_token = malloc(sizeof(t_token));
	// if (!new_token)
ctx->last_error = ctx->last_error;
	// 	ft_error(ctx, "");
	new_token->type = key;
	new_token->value = value;
	new_entry = ft_lstnew(new_token);
	// if (!new_entry)
	// 	ft_error(ctx, "malloc"))
	ft_lstadd_back(token_lst, new_entry);
}

char	*ft_get_part(t_ctx *ctx, char *str, char end)
{
	char	*result;
	size_t	size;

	size = 0;
	while (str[size] != end)
		size++;
	result = ft_substr(str, 0, size);
	// if (!result && size)
ctx->last_error = ctx->last_error;
		// ft_error("malloc")
	return (result);
}

char	*ft_add_part(t_ctx *ctx, char *tmp, char *str)
{
	char	*result;

	if (!tmp)
		return (str);
	result = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
	// if (!result)
ctx->last_error = ctx->last_error;
	// 	ft_error("malloc")
	return (result);
}


