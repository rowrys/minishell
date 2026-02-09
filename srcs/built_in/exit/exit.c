/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:45:27 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:21:01 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static void	ft_exit_error(t_ctx *ctx, char *str, char **argv)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_double(&argv);
	ft_destroy_ctx(ctx);
	exit(2);
}

static bool	ft_skip_undesirable(t_ctx *ctx, char *nptr, size_t *i, char **argv)
{
	bool	is_negative;
	char	*str;
	size_t	size;
	size_t	j;

	*i += ft_skip(&nptr[*i], ISSPACE);
	is_negative = false;
	if (nptr[*i] == '-')
		is_negative = true;
	if (nptr[*i] == '+' || nptr[*i] == '-')
		(*i)++;
	size = ft_skip(&nptr[*i], DIGIT);
	j = ft_skip(&nptr[size + *i], ISSPACE) + size + *i;
	if (nptr[j])
		ft_exit_error(ctx, nptr, argv);
	str = ft_substr(nptr, *i, size);
	if (!str)
		ft_free_db_and_error(argv, ctx, MALLOC_ERROR, EXIT_FAILURE);
	if (ft_is_overflow(str, is_negative))
	{
		free(str);
		ft_exit_error(ctx, nptr, argv);
	}
	free(str);
	return (is_negative);
}

static size_t	ft_atoll(t_ctx *ctx, char *nptr, char **argv)
{
	long long	res;
	size_t		i;
	bool		is_neg;

	i = 0;
	is_neg = ft_skip_undesirable(ctx, nptr, &i, argv);
	res = 0;
	while (ft_isdigit(nptr[i]))
		res = res * 10 + nptr[i++] - '0';
	if (is_neg)
		res = -res;
	res = res % 256;
	return (res);
}

static void	ft_exit_really(t_ctx *ctx, char *str, char **argv)
{
	size_t	result;

	result = 0;
	if (str)
		result = ft_atoll(ctx, str, argv);
	ft_putstr_fd("exit\n", 2);
	ft_free_double(&argv);
	ft_destroy_ctx(ctx);
	exit(result);
}

void	ft_exit(t_ctx *ctx, bool is_child, size_t argc, char **argv)
{
	if (argc == 1)
		ft_exit_really(ctx, NULL, argv);
	if (argc == 2)
		ft_exit_really(ctx, argv[1], argv);
	if (argc == 3)
	{
		if (ft_str_only_contain(argv[1], VALID_CHAR))
		{
			write(2, "exit\nminishell: exit: too many arguments\n", 41);
			ft_free_double(&argv);
			if (is_child)
			{
				ft_destroy_ctx(ctx);
				exit(1);
			}
			ctx->last_error = 1;
			return ;
		}
		ft_exit_error(ctx, argv[1], argv);
	}
	write(2, "exit\nminishell: exit: too many arguments\n", 41);
	ft_free_double(&argv);
	ft_destroy_ctx(ctx);
	exit(2);
}
