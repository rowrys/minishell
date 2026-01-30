/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:44:19 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/29 14:51:39 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"

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
