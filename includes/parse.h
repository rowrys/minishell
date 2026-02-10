/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:22:52 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/10 09:35:30 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include <stdbool.h>

/*parse*/
void	ft_parse(t_ctx *ctx);

/*parse_line*/
void	ft_parse_line(t_ctx *ctx);

/*parse_block*/
bool	ft_parse_expand(t_ctx *ctx, t_list **new_list, t_token *token,
			char **result);
void	ft_parse_block(t_ctx *ctx, t_token *token, char **result);
void	ft_parse_quote(t_ctx *ctx, t_token *token, char **result);

/*valid_line*/
bool	ft_is_empty(t_ctx *ctx, char *str);
bool	ft_is_valid_line(t_ctx *ctx, char *str);

/*syntax_error*/
bool	ft_is_syntax_error_quote(char *str);
bool	ft_is_syntax_error_pipe(char *str);
bool	ft_is_syntax_error_redir(char *str);
bool	ft_is_syntax_error_redir_here_doc(char *str);


/*expand*/
char	*ft_manage_expand(t_ctx *ctx, char *str, bool skip_quote);
char	*ft_expand(t_ctx *ctx, char *str, size_t size);
size_t	ft_explen(char *str);

/*get_next_token*/
t_list	*ft_get_next_token(t_ctx *ctx, t_key key, size_t *i);

/*parse_token_list*/
t_list	*ft_parse_token_list(t_ctx *ctx, t_list *old_lst);

#endif