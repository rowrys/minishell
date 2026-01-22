/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:44:19 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 14:32:53 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "minishell.h"
#include "parse.h"
#include "utils.h"

bool	ft_is_valid_redir_parts(char *str)
{
	while (*str)
	{
		str += ft_skip(str, ISSPACE);
		if (*str == '\'' || *str == '"')
			str += ft_go_to(str + 1, *str) + 1;
		else if (*str == '<' || *str == '>')
		{
			if (!ft_get_redir_key(str))
				return (false);
			str += ft_skip(str, "<>");
			str += ft_skip(str, ISSPACE);
			if (ft_strchr(TOKEN_LIMITER, *str))
				return (false);
			else
				str++;
		}
		else if (*str)
			str++;
	}
	return (true);
}

bool	ft_is_valid_pipe_parts(char *str)
{
	if (*str == '|')
		return (false);
	while (*str)
	{	
		if (*str == '\'' || *str == '"')
			str += ft_go_to(str + 1, *str) + 1;
		else if (*str == '|')
		{
			str++;
			if (ft_strchr(ISSPACE, *str))
				str += ft_skip(str, ISSPACE);
			if (!*str || *str == '|')
				return (false);
			else
				str++;
		}
		else if (*str)
			str++;
	}
	return (true);
}

bool	ft_is_valid_quote_parts(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		str += ft_skip(str, ISSPACE);
		if (*str == '\'' || *str == '"')
		{
			str += ft_go_to(str + 1, *str) + 1;
			if (*str == '\'' || *str == '"')
				str++;
			else
				return (false);
		}
		else if (*str)
			str++;
	}
	return (true);
}

bool	ft_have_syntax_error(char *str)
{
	str += ft_skip(str, ISSPACE);
	if (ft_is_valid_quote_parts(str) == false)
		return (true);
	if (ft_is_valid_pipe_parts(str) == false)
		return (true);
	if (ft_is_valid_redir_parts(str) == false)
		return (true);
	return (false);
}
