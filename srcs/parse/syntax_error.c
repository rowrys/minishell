/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:44:19 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/12 09:46:50 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"

#include <stdbool.h>

bool	ft_is_syntax_error_redir(char *str)
{
	str += ft_skip(str, ISSPACE);
	while (*str)
	{
		str += ft_skip(str, ISSPACE);
		if (*str == '\'' || *str == '"')
			str += ft_go_to(str + 1, *str) + 2;
		else if (*str == '<' || *str == '>')
		{
			if (!ft_get_redir_key(str))
				return (true);
			str += ft_skip(str, "<>");
			str += ft_skip(str, ISSPACE);
			if (ft_strchr(TOKEN_LIMITER, *str))
				return (true);
		}
		else if (*str)
			str++;
	}
	return (false);
}

static int	ft_skip_invalid_redir(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '<' || str[i] == '>')
	{
		if (!ft_get_redir_key(str + i))
			return (true);
		i += ft_skip(str + i, "<>");
		i += ft_skip(str + i, ISSPACE);
	}
	return (i);
}

bool	ft_is_syntax_error_pipe(char *str)
{
	str += ft_skip(str, ISSPACE);
	str += ft_skip_invalid_redir(str);
	if (*str == '|')
		return (true);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str += ft_go_to(str + 1, *str) + 2;
		else if (*str == '|')
		{
			str++;
			if (ft_strchr(ISSPACE, *str))
				str += ft_skip(str, ISSPACE);
			if ((*str == '<' || *str == '>')
				&& *(str + ft_skip_invalid_redir(str)) != '\0')
				str += ft_skip_invalid_redir(str);
			if (!*str || *str == '|')
				return (true);
		}
		else if (*str == '<' || *str == '>')
			str += ft_skip_invalid_redir(str);
		else if (*str)
			str++;
	}
	return (false);
}

bool	ft_is_syntax_error_quote(char *str)
{
	while (*str)
	{
		str += ft_skip(str, ISSPACE);
		if (*str == '\'' || *str == '"')
		{
			str += ft_go_to(str + 1, *str) + 1;
			if (*str == '\'' || *str == '"')
				str++;
			else
				return (true);
		}
		else if (*str)
			str++;
	}
	return (false);
}
