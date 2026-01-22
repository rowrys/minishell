/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:26:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 13:41:06 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ctx.h"
#include "parse.h"
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <strings.h>

int	main(int argc, char **argv, char **env)
{
	t_ctx	ctx;

	(void)argv;
	ft_init_ctx(&ctx, argc, env);
    while (1)
    {
        ctx.line = readline("minishell>");
		if (!ctx.line)
			break ;
		if (*ctx.line)
			add_history(ctx.line);
		if (ft_is_valid_line(&ctx, ctx.line))
		{
			ft_parse(&ctx);
			// ft_execute(&ctx);
		}
		ft_clean_ctx(&ctx);
    }
	ft_destroy_ctx(&ctx);
	rl_clear_history();
	return (0);
}
