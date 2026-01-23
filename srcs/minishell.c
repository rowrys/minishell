/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:26:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/23 11:15:42 by mcolin           ###   ########.fr       */
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
			

			t_list	*cmd_lst;
			t_list	*token_lst;
			t_token	*token;
			t_cmd	*cmd;

			cmd_lst = ctx.cmd_lst;
			while (cmd_lst)
			{
				cmd = cmd_lst->content;
				token_lst = cmd->token;				
				while (token_lst)
				{
					#include <stdio.h>
					token = token_lst->content;
					printf("%d:%s\n", token->type, token->value);
					token_lst = token_lst->next;
				}
				cmd_lst = cmd_lst->next;
			}





			// ft_execute(&ctx);
		}
		ft_clean_ctx(&ctx);
    }
	ft_destroy_ctx(&ctx);
	rl_clear_history();
	return (0);
}
