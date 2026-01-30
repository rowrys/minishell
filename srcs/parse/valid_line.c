/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:59:51 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/29 14:14:17 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "parse.h"
#include <stdbool.h>

bool	ft_is_empty(t_ctx *ctx, char *str)
{
	char	*line;
	int		i;

	line = ft_strdup(str);
	//if (!line)
ctx->last_error = ctx->last_error;
	//	ft_error(malloc);
	
	line = ft_manage_expand(ctx, line, 1);
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
		ft_putendl_fd("minishell: syntax error near unexpected token 'quote'", 2);		
		ctx->last_error = 2;
		is_valid = false;
	}
	if (is_valid && ft_is_empty(ctx, str))
		is_valid = false;
	return (is_valid);
}
