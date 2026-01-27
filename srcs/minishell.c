/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:26:55 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/26 17:11:30 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ctx.h"
#include "parse.h"
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <strings.h>

/************************************************************* 
 * REMOVE THIS */

const char	*t_key_tostr(t_key k)
{
	switch (k)
	{
		case KEY_END: return "KEY_END";
		case KEY_PIPE: return "KEY_PIPE";
		case KEY_CHUNK: return "KEY_CHUNK";
		case KEY_REDIR: return "KEY_REDIR";
		case KEY_LREDIR: return "KEY_LREDIR";
		case KEY_RREDIR: return "KEY_RREDIR";
		case KEY_APPEND: return "KEY_APPEND";
		case KEY_HERE_DOC: return "KEY_HERE_DOC";
	}
	return "UNKNOWN";
}

#include <stdio.h>
/***********************************************************/

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
					token = token_lst->content;
					printf("%s:[%s]\n", t_key_tostr(token->type), token->value);
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
