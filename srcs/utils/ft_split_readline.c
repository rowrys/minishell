/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_readline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 10:40:00 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:17:12 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"

static int	ft_count_array(char const *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

static char	**ft_split_error(t_ctx *ctx, char *line, char sep)
{
	char	**ptr;
	size_t	i;
	size_t	size;
	size_t	nb_array;

	nb_array = ft_count_array(line, sep);
	ptr = ft_calloc(sizeof(char **), (nb_array + 1));
	if (!ptr)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	i = -1;
	while (++i < nb_array)
	{
		while (line && *line == sep)
			line++;
		size = 0;
		while (*(line + size) && *(line + size) != sep)
			size++;
		ptr[i] = ft_substr(line, 0, size);
		if (!ptr[i])
			ft_free_double(&ptr);
		if (!ptr || !ptr[i])
			ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
		line += size;
	}
	return (ptr);
}

void	ft_split_readline(t_ctx *ctx)
{
	char	**line_split;
	char	*line;

	line = ft_strdup(ctx->line);
	if (!line)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	line_split = ft_split_error(ctx, line, '\n');
	ctx->line_split = line_split;
	free(line);
}
