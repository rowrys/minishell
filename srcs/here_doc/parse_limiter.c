/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_limiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 11:35:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/03 15:01:39 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>

bool    ft_check_limiter(char *line, char *limiter, int *total_size_write)
{
    if (ft_strcmp(line, limiter) == 0)
        return (true);
    *total_size_write += ft_strlen(line);
	if (*total_size_write >= 65536)
	{
		ft_putendl_fd("Error : here_doc, the pipe capacity is 16 pages", 2);
		free(line);
	}
	else if (!line)
		ft_putendl_fd("Error : here_doc, not finished as intended", 2);
	else
		return (false);
	return (true);
}

static void ft_parse_limiter_quote(t_ctx *ctx, char *block, size_t *i, char **limiter)
{
    char    *part;

    part = ft_get_part(ctx, block + *i + 1, block[*i]);
    *limiter = ft_add_part(ctx, *limiter, part);
    *i += ft_go_to(block + *i + 1, block[*i]) + 2;
}

static void ft_parse_limiter_block(t_ctx *ctx, char *block, size_t *i, char **limiter)
{
    char    *part;
    size_t  size;

    size = 0;
    while (block[*i + size] && block[*i + size] != '"' && block[*i + size] != '\'')
        size++;
    part = ft_substr(block + *i , 0, size);
    if (!part)
	{
    	free(limiter);  
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
    *limiter = ft_add_part(ctx, *limiter, part);
    *i += size;
}

static char	*ft_parse_limiter(t_ctx *ctx, char *block)
{
	char    *limiter;
	size_t	i;

    limiter = NULL;
	i = 0;
    while (block[i])
    {
        if (block[i] == '"' || block[i] == '\'')
            ft_parse_limiter_quote(ctx, block, &i, &limiter);
        else
            ft_parse_limiter_block(ctx, block, &i, &limiter);
    }
	return (limiter);
}

char	*ft_get_limiter(t_ctx *ctx, char *block, bool *do_expand)
{
	char	*limiter;

	if (ft_strchr(block, '"') || ft_strchr(block, '\''))
	{
		*do_expand = false;
		limiter = ft_parse_limiter(ctx, block);
	}
	else
    {
		limiter = ft_strdup(block);
        if (!limiter)
            ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
    }
	return (limiter);
}
