/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:45:27 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/06 21:08:48 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "ctx.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>

#define DIGIT "0123456789"

static long long ft_atoll(char *nptr, bool *have_error)
{
	long long	res;
	long long	tmp;
	size_t		i;
	char		cond;

	// cond = 1;
	// i = 0;
	// res = 0;
	// *have_error = 0;
	// while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
	// 	i++;
	// if (nptr[i] == '-')
	// 	cond *= -1;
	// if (nptr[i] == '+' || nptr[i] == '-')
	// 	i++;
	// if (!ft_isdigit(nptr[i]))
	// 	ft_ex
	while (ft_isdigit(nptr[i]))
	{
		tmp = res;
		res = res * 10 + nptr[i++] - '0';
		if ((long long)tmp > (long long)res)
			*have_error = 1;
	}
	return (res * cond);
}

static void	ft_exit_really(t_ctx *ctx, char *str)
{
	size_t	result;
	bool	have_overflow;

	ft_destroy_ctx(ctx);
	ft_putstr_fd("exit\n", 2);
	result = ft_atoll(str, &have_overflow);
	if (have_overflow)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	exit((unsigned char)result % 256);
}

void	ft_exit(t_ctx *ctx, bool is_child, int argc, char **argv)
{
	(void)is_child;

	if (argc == 2)
		ft_exit_really(ctx, argv[1]);
	if (argc == 3 && !ft_skip(argv[3], DIGIT))
	{
		ft_destroy_ctx(ctx);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	write(2, "exit\nminishell: exit: too many arguments", 40);
}
