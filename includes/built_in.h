/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 09:49:20 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/08 18:33:41 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include <stdbool.h>
#include <stddef.h>

typedef void	(*t_builtin_func)(t_ctx *, bool, size_t, char**);

#define VALID_CHAR "\t\n\v\f\r 0123456789"
#define DIGIT "0123456789"
#define LLONG_MAX 9223372036854775807
#define LLONG_MIN 9223372036854775808
#define NB_DIGIT_LL	19

#define NO_DIRECTORY "minishell: cd: No such file or directory"

#define EXPORT_LIMITER "'\"=\t\n\v\f\r ?"

/*env*/
void    ft_env(t_ctx *ctx, bool is_clone, size_t argc, char **argv);

/*exit*/
void	ft_exit(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*exit_utils*/
char	ft_str_only_contain(const char *s1, const char *s2);
bool	ft_is_overflow(char *str, bool is_neg);

/*echo*/
void	ft_echo(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*pwd*/
void    ft_pwd(t_ctx *ctx, bool is_clone, size_t argc, char **argv);

/*cd*/
void    ft_cd(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*cd_utils*/
void    ft_manage_cdpath(t_ctx *ctx, bool is_child, char **cdpath,
                            char **argv);
void    ft_cd_check_dir(t_ctx *ctx, bool is_child, char *path, char **argv);

/*cd_utils2*/
void    ft_set_pwd(t_ctx *ctx, char **argv);

/*ft_export*/
void    ft_export(t_ctx *ctx, bool is_clone, size_t argc, char **argv);
bool	ft_is_valid_identifier(char *str);
char	*ft_get_key(t_ctx *ctx, char **argv, char *str);
char	*ft_get_value(t_ctx *ctx, char **argv, char *str, char *free_42_angouleme);


#endif