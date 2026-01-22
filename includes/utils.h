/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:50:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/22 10:34:12 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*parse_utils*/
int		ft_get_redir_key(char *str);
void	ft_add_token(t_ctx *ctx, t_list **token_lst, int key, char *value);
char	*ft_get_part(t_ctx *ctx, char *str, char end);
char	*ft_add_part(t_ctx *ctx, char *tmp, char *str);

/*utils*/
int		ft_go_to(char *str, char c);
int		ft_skip(char *str, char *charset);

/*env_utils*/
char	*ft_get_dict_value(t_ctx *ctx, t_list *tmp_dict, char *name);

#endif