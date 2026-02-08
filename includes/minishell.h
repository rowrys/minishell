/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:03:14 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/08 12:58:56 by ykolacze         ###   ########.fr       */
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
#include <sys/types.h>

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

typedef enum e_built_in
{
	BUILT_IN_ECHO,
	BUILT_IN_CD,
	BUILT_IN_PWD,
	BUILT_IN_EXPORT,
	BUILT_IN_ENV,
	BUILT_IN_EXIT,
	BUILT_IN_UNSET,
	BUILT_IN_ENUM_MAX,
}	t_built_in;

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
	int		pipe_hd[2];
	int		pipe_cmd[2];
	pid_t	cpid;
}			t_cmd;

typedef struct s_ctx
{
	char	*line;
	char	**line_split;
	t_list	*cmd_lst;
	t_list	*env_dict;
	t_list	*declare_x;
	int		last_error;
	int		stdin_fileno;
	int		stdout_fileno;
}			t_ctx;

#endif