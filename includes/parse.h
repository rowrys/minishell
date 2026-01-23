/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:22:52 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/23 14:05:52 by mcolin           ###   ########.fr       */
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

/*env_utils*/
int		ft_get_redir_key(char *str);

/*valid_line*/
bool	ft_is_empty(t_ctx *ctx, char *str);
bool	ft_is_valid_line(t_ctx *ctx, char *str);

/*syntax_error*/
bool	ft_have_syntax_error(char *str);
bool	ft_is_valid_quote_parts(char *str);
bool	ft_is_valid_pipe_parts(char *str);
bool	ft_is_valid_redir_parts(char *str);

/*expand*/
char	*ft_manage_expand(t_ctx *ctx, char *str, bool skip_quote);
char	*ft_expand(t_ctx *ctx, char *str, size_t size);
size_t	ft_explen(char *str);

/*get_next_token*/
t_list *ft_get_next_token(t_ctx *ctx, t_key key, size_t *i);

/*parse_token_list*/
t_list *ft_parse_token_list(t_ctx *ctx, t_list *old_lst);

#endif