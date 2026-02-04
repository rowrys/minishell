/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:50:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/04 10:26:33 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <stdbool.h>

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_PERMISSION_DENIED 126

# define MALLOC_ERROR "Malloc exploded, how did you do that???"
 
/*parse_utils*/
int		ft_get_redir_key(char *str);
void	ft_add_token(t_ctx *ctx, t_list **token_lst, int key, char *value);
char	*ft_get_part(t_ctx *ctx, char *str, char end);
char	*ft_add_part(t_ctx *ctx, char *result, char *part);
bool    ft_is_inside_quote(char *str);

/*ft_split_readline*/
void	ft_split_readline(t_ctx *ctx);

/*ft_split_expand*/
char    **ft_split_expand(t_ctx *ctx, char *str);

/*utils*/
int		ft_go_to(char *str, char c);
int		ft_skip(char *str, char *charset);
bool	ft_is_redir_key(t_key key);

/*close*/
void	ft_replace_fd(int *old_fd, int new_fd);
void	ft_close_cmd_fds(t_cmd *cmd);
void	ft_close(int *fd);
void    ft_error(t_ctx *ctx, char *msg, int code);

/*error*/
void    ft_error(t_ctx *ctx, char *msg, int code);
void	ft_access_denied(t_ctx *ctx, char **splited_path, char *binary, char **env);
void    ft_cmd_not_found(t_ctx *ctx, char *binary, char **env);

/*free*/
void	ft_free_and_error(char *to_free, t_ctx *ctx, char *msg, int code);
void	ft_free_db_and_error(char **to_free, t_ctx *ctx, char *msg, int code);

/*env_utils*/
char	*ft_get_dict_value(t_ctx *ctx, t_list *tmp_dict, char *name);
char	**ft_env_to_array(t_ctx *ctx, t_list *env_dict);

#endif