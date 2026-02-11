/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 17:21:38 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 22:45:19 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ctx.h"
#include "libft.h"
#include "minishell.h"
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

static char	*ft_get_value(t_ctx *ctx, char **argv, char *str,
		char *free_42_angouleme)
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

static char	*ft_get_key(t_ctx *ctx, char **argv, char *str)
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

t_list	*ft_creat_lst_dict_entry(t_ctx *ctx, char **argv, char *str)
{
	char			*key;
	char			*value;
	t_dict_entry	*dict_entry;
	t_list			*result;

	key = ft_get_key(ctx, argv, str);
	value = ft_get_value(ctx, argv, str, key);
	dict_entry = ft_calloc(1, sizeof(t_dict_entry));
	if (!dict_entry)
	{
		free(value);
		free(key);
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	dict_entry->key = key;
	dict_entry->value = value;
	result = ft_lstnew(dict_entry);
	if (!result)
	{
		ft_destroy_dict_entry(dict_entry);
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	}
	return (result);
}
