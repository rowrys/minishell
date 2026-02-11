/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:50:50 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/11 09:06:22 by ykolacze         ###   ########.fr       */
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
bool	ft_is_inside_quote(char *str);

/*ft_split_readline*/
void	ft_split_readline(t_ctx *ctx);

/*ft_split_expand*/
char	**ft_split_expand(t_ctx *ctx, char *str);

/*utils*/
int		ft_go_to(char *str, char c);
int		ft_skip(char *str, char *charset);
bool	ft_is_redir_key(t_key key);

/*exec_utils*/
int		ft_dup(int fd, int fd2);
char	*ft_check_bin_42_angouleme(t_ctx *ctx, char **splited_path, size_t i,
			char *binary);
char	*ft_check_bin_denied_42_angouleme(t_ctx *ctx, char **splited_path,
			size_t i, char *binary);
bool	ft_is_dir(char *bin);
bool	ft_is_reg(char *bin);

/*close*/
void	ft_replace_fd(int *old_fd, int new_fd);
void	ft_close_cmd_fds(t_cmd *cmd);
void	ft_close(int *fd);
void	ft_error(t_ctx *ctx, char *msg, int code);

/*error*/
void	ft_error(t_ctx *ctx, char *msg, int code);
void	ft_error_execve(t_ctx *ctx, char *msg, int errno_tmp);
void	ft_cmd_not_found(t_ctx *ctx, char *binary, char **env);
void	ft_cd_error(bool is_child, t_ctx *ctx, char *msg, int code);

/*free*/
void	ft_free_and_error(char *to_free, t_ctx *ctx, char *msg, int code);
void	ft_free_db_and_error(char **to_free, t_ctx *ctx, char *msg, int code);
void	ft_lst_db_str_malloc(t_ctx *ctx, t_list *lst_42, char **db_str_42,
			char *str_42);
void	ft_free_lst_db_strs(t_list *lst_42, char **db_str_42, char *str_42,
			char *str42_2);

/*env_utils*/
char	*ft_triple_join(t_ctx *ctx, char *key, char *sep, char *value);
char	*ft_get_dict_value(t_ctx *ctx, t_list *tmp_dict, char *name);
char	**ft_env_to_array(t_ctx *ctx, t_list *env_dict);
char	*ft_get_entry_ptr(t_ctx *ctx, char *key);

#endif