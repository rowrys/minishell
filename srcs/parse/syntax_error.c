/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:44:19 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 11:42:12 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"
#include <stdbool.h>

# define HERE_DOC_LIMITER "|<>\0"

bool	ft_is_syntax_error_redir_here_doc(char *str)
{
	str += ft_skip(str, ISSPACE);
	while (*str)
	{
		str += ft_skip(str, ISSPACE);
		if (*str == '\'' || *str == '"')
			str += ft_go_to(str + 1, *str) + 2;
		else if (*str == '<' && *(str + 1) == '<')
		{
			if (ft_strchr(HERE_DOC_LIMITER, *(str + 2)))
				return (true);
			str += 2;
			str += ft_skip(str, ISSPACE);
			if (ft_strchr(HERE_DOC_LIMITER, *str))
				return (true);
		}
		else if (*str)
			str++;
	}
	return (false);
}

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

bool	ft_is_syntax_error_pipe(char *str)
{
	str += ft_skip(str, ISSPACE);
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
			if (!*str || *str == '|')
				return (true);
		}
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
