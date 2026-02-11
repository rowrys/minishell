/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:38:26 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/11 21:04:17 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

#include <stdbool.h>
#include <stdio.h>

void	ft_exit_write_error(bool is_child)
{
	if (!is_child)
		write(2, "exit\n", 5);
	write(2, "minishell: exit: too many arguments\n", 36);
}

bool	ft_is_overflow(char *str, bool is_neg)
{
	size_t	len_str;

	while (*str == '0')
		str++;
	if (!*str)
		return (false);
	len_str = ft_strlen(str);
	if (len_str > NB_DIGIT_LL)
		return (true);
	else if (len_str < NB_DIGIT_LL)
		return (false);
	if (is_neg)
	{
		if (ft_strcmp(str, "9223372036854775808") < 0)
			return (true);
		return (false);
	}
	if (ft_strcmp(str, "9223372036854775807") > 0)
		return (true);
	return (false);
}

char	ft_str_only_contain(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(s2, s1[i]) == NULL)
			break ;
		i++;
	}
	if (!s1[i])
		return (true);
	return (false);
}
