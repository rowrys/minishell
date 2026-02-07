/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:18:59 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/07 20:44:12 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "ctx.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

static void	ft_write_error(t_ctx *ctx, bool is_child, char **argv)
{
	if (is_child)
	{
		ft_free_double(&argv);
		ft_destroy_ctx(ctx);
		exit(1);
	}
	ctx->last_error = 1;
}

static void	ft_end_echo(t_ctx *ctx, bool is_child, char **argv, bool delete_new_line)
{
	if (delete_new_line != true)
	{
		if (write(1, "\n", 1))
			ft_write_error(ctx, is_child, argv);
		}
	if (is_child)
	{
		ft_free_double(&argv);
		ft_destroy_ctx(ctx);
		exit(0);
	}
	ctx->last_error = 0;
}

static bool	ft_check_option(char *str, bool *delete_new_line)
{
	size_t	i;

	i = 0;
	if (str[i++] == '-')
	{
		if (str[i] != 'n')
			return (true);
		while (str[i] == 'n')
			i++;
		if (!str[i])
		{
			*delete_new_line = true;
			return (false);
		}
	}
	return (true);
}

void	ft_echo(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	size_t	i;
	bool	delete_new_line;
	(void)argc;

	delete_new_line = false;
	i = 1;
	while (argv[i])
	{
		if (ft_check_option(argv[i], &delete_new_line))
		{
			if (write(1, argv[i], ft_strlen(argv[i])))
				ft_write_error(ctx, is_child, argv);
			i++;
			if (argv[i])
			{
				if (write(1, " ", 1))
					ft_write_error(ctx, is_child, argv);
			}
		}
		else
			i++;
	}
	ft_end_echo(ctx, is_child, argv, delete_new_line);
}
