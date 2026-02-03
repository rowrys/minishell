/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:52:28 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 17:46:23 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include <stdlib.h>

static void	ft_arg_cpy(t_ctx *ctx, t_cmd *cmd, char **buffer)
{
	t_list	*origin;
	t_token	*token;
	size_t	i;

	i = 0;
	origin = cmd->token;
	while (origin)
	{
		token = origin->content;
		if (token->type == KEY_CHUNK)
		{
			buffer[i] = ft_strdup(token->value);
			if (!buffer[i])
			{
				ft_free_double(&buffer);
				ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
			}
			i++;
		}
		origin = origin->next;
	}
}

char	**ft_cmd_to_arg(t_ctx *ctx, t_cmd *cmd)
{
	t_list	*token_list;
	t_token	*token;
	size_t	nb_chunk;
	char 	**result;

	nb_chunk = 0;
	token_list = cmd->token;
	while (token_list)
	{
		token = token_list->content;
		if (token->type == KEY_CHUNK)
			nb_chunk++;
		token_list = token_list->next;
	}
	result = ft_calloc(nb_chunk + 1, sizeof(char *));
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	ft_arg_cpy(ctx, cmd, result);
	return (result);
}
