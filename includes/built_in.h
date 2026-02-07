/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 09:49:20 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/07 20:17:22 by mcolin           ###   ########.fr       */
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

/*ENV*/
void    ft_env(t_ctx *ctx, bool is_clone, size_t argc, char **argv);

/*exit*/
void	ft_exit(t_ctx *ctx, bool is_child, size_t argc, char **argv);

/*exit_utils*/
char	ft_str_only_contain(const char *s1, const char *s2);
bool	ft_is_overflow(char *str, bool is_neg);

/*echo*/
void	ft_echo(t_ctx *ctx, bool is_child, size_t argc, char **argv);


#endif