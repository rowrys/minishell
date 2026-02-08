/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:21:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/08 17:47:52 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>

bool	ft_is_valid_identifier(char *str)
{
	size_t	i;

	i = 0;
	if (ft_strchr(EXPORT_LIMITER, *str))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (false);
	}
	while (!ft_strchr(EXPORT_LIMITER, str[i]))
		i++;
	if (!str[i] || str[i] == '=')
		return (true);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (false);
}

char	*ft_get_value(t_ctx *ctx, char **argv, char *str, char *free_42_angouleme)
{
	char	*value;

	value = ft_strchr(str, '=');
	if (!value)
		return (NULL);
	value = ft_substr(value, 1, ft_strlen(value));
	if (!value)
	{
		free(free_42_angouleme);
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);		
	}
	return (value);
}

char	*ft_get_key(t_ctx *ctx, char **argv, char *str)
{
	char	*key;
	size_t	size;

	key = ft_strchr(str, '=');
	if (!key)
		size = ft_strlen(str);
	else
		size = key - str;
	key = ft_substr(str, 0, size);
	if (!key)
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	return (key);
}
