/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:22:52 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 11:37:37 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include <stdbool.h>

/*parse*/
void	ft_parse(t_ctx *ctx);

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

#endif