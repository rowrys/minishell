/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:03:14 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/27 16:20:31 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ISSPACE "\t\n\v\f\r \0"
# define TOKEN_LIMITER "|<>\t\n\v\f\r \0"
# define EXPAND_LIMITER "'\"$|<>\t\n\v\f\r \0"
# define REDIR_SKIP "<>\t\n\v\f\r \0"
# define PART_LIMITER "$'\"\0"

# include "libft.h"

typedef enum e_key
{
	KEY_END,
	KEY_PIPE,
	KEY_CHUNK,
	KEY_REDIR,
	KEY_LREDIR,
	KEY_RREDIR,
	KEY_APPEND,
	KEY_HERE_DOC
}	t_key;

typedef struct s_dict_entry
{
	char	*key;
	char	*value;
}			t_dict_entry;

typedef struct s_token
{
	char	*value;
	t_key	type;
}			t_token;

typedef struct s_cmd
{
	t_list	*token;
	int		fd_in;
	int		fd_out;
}			t_cmd;

typedef struct s_ctx
{
	char	*line;
	t_list	*cmd_lst;
	t_list	*env_dict;
	int		last_error;
}			t_ctx;

#endif