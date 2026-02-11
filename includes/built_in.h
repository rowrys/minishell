/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 09:49:20 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/11 21:05:08 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "libft.h"
# include "minishell.h"

# include <stdbool.h>
# include <stddef.h>

typedef void	(*t_builtin_func)(t_ctx *, bool, size_t, char **);

# define VALID_CHAR "\t\n\v\f\r 0123456789"
# define DIGIT "0123456789"

# define NB_DIGIT_LL 19

# define EXPORT_LIMITER "<>|'\"=\t\n\v\f\r ?"

# define NO_DIRECTORY "minishell: cd: No such file or directory"

# define NO_PARENT_DIR \
	"cd: error retrieving current directory: getcwd: \
cannot access parent directories"

# define CHDIR_ERROR "minishell: cd: chdir: "

/*env*/
void			ft_env(t_ctx *ctx, bool is_clone, size_t argc, char **argv);

/*exit*/
void			ft_exit(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*exit_utils*/
char			ft_str_only_contain(const char *s1, const char *s2);
bool			ft_is_overflow(char *str, bool is_neg);
void			ft_exit_write_error(bool is_child);

/*echo*/
void			ft_echo(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*pwd*/
void			ft_pwd(t_ctx *ctx, bool is_clone, size_t argc, char **argv);

/*cd*/
void			ft_cd(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*cd_utils*/
void			ft_manage_cdpath(t_ctx *ctx, bool is_child, char **cdpath,
					char **argv);

/*cd_utils2*/
bool			ft_is_valid_cd(t_ctx *ctx, bool is_child, size_t argc,
					char **argv);
void			ft_cd_no_parent(char **argv, char *str, t_ctx *ctx,
					bool is_child);

/*cd_utils3*/
void			ft_repl_entry_value(t_ctx *ctx, char *key, char *value,
					char **free_42);

/*export*/
void			ft_export(t_ctx *ctx, bool is_clone, size_t argc, char **argv);
void			ft_put_in_env(t_ctx *ctx, t_list *new_node);

/*export_declare_x*/
void			ft_replace_node_dict_entry(t_list *current, t_list *new_node);
void			ft_put_in_declare_x(t_ctx *ctx, t_list *new_node);

/*expend_parse*/
t_list			*ft_creat_lst_dict_entry(t_ctx *ctx, char **argv, char *str);
bool			ft_is_valid_identifier(char *str);

/*unset*/
void			ft_unset(t_ctx *ctx, bool is_child, size_t argc, char **argv);

#endif