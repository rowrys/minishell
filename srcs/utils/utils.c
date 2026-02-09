/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:52:28 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:17:24 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>

bool	ft_is_redir_key(t_key key)
{
	if (key == KEY_LREDIR || key == KEY_RREDIR || key == KEY_HERE_DOC
		|| key == KEY_APPEND)
		return (true);
	return (false);
}

int	ft_go_to(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_skip(char *str, char *charset)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && ft_strchr(charset, str[i]))
		i++;
	return (i);
}

char	*ft_triple_join(t_ctx *ctx, char *key, char *sep, char *value)
{
	char	*result;
	char	*tmp;

	(void)ctx;
	result = ft_strdup(key);
	if (!result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	tmp = ft_strjoin(result, sep);
	free(result);
	if (!tmp)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	result = ft_strjoin(tmp, value);
	free(tmp);
	if (value && !result)
		ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
	return (result);
}
