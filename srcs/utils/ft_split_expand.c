/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:17:38 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/03 15:13:14 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdlib.h>

static size_t   ft_blocklen(char *s)
{
    size_t  size;

    size = 0;
    while (s[size] && !ft_strchr(ISSPACE, s[size]))
    {
        if (s[size] == '"' || s[size] == '\'')
            size += ft_go_to(&s[size + 1], s[size]) + 2;
        else
            size++;
    }
    return (size);
}

static size_t	ft_count_array(char *s)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s && s[i])
	{
        if (ft_strchr(ISSPACE, s[i]))
            i += ft_skip(&s[i], ISSPACE);
		if (s[i])
		{
			counter++;
			i += ft_blocklen(&s[i]);
		}
	}
	return (counter);
}

char    **ft_split_expand(t_ctx *ctx, char *str)
{
	char	**result;
	size_t	i;
	size_t	size;
	size_t	nb_array;

	nb_array = ft_count_array(str);
	result = ft_calloc(sizeof(char *), (nb_array + 1));
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	i = 0;
	while (i < nb_array)
	{
		while (ft_strchr(ISSPACE, *str))
            str++;
		size = ft_blocklen(str);
		result[i] = ft_substr(str, 0, size);
		if (!result[i])
        {
			ft_free_double(&result);
	        ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
        }
		str += size;
        i++;
	}
	return (result);
}
