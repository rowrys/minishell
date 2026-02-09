/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:22:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:19:22 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool	ft_is_inside_quote(char *str)
{
	if (*str == '"' && str[ft_strlen(str) - 1] == '"')
		return (true);
	if (*str == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (true);
	return (false);
}

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
	if (!new_token)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	new_token->type = key;
	new_token->value = value;
	new_entry = ft_lstnew(new_token);
	if (!new_entry)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_lstadd_back(token_lst, new_entry);
}

char	*ft_get_part(t_ctx *ctx, char *str, char end)
{
	char	*result;
	size_t	size;

	size = 0;
	while (str[size] && str[size] != end)
		size++;
	result = ft_substr(str, 0, size);
	if (!result && size)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	return (result);
}

char	*ft_add_part(t_ctx *ctx, char *result, char *part)
{
	char	*to_return;

	if (!part)
		return (result);
	if (!result)
		to_return = ft_strdup(part);
	else
		to_return = ft_strjoin(result, part);
	free(result);
	result = NULL;
	free(part);
	part = NULL;
	if (!to_return)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	return (to_return);
}
