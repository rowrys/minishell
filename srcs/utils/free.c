/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:20:35 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/11 21:01:11 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

void	ft_free_all(t_ctx *ctx, t_list *lst_42, char **db_str_42, char *str_42)
{
	if (str_42)
		free(str_42);
	if (db_str_42)
		ft_free_double(&db_str_42);
	if (lst_42)
		ft_lstclear(&lst_42, &ft_destroy_dict_entry);
	ft_destroy_ctx(ctx);
}

void	ft_free_lst_db_strs(t_list *lst_42, char **db_str_42, char *str_42,
		char *str42_2)
{
	if (str_42)
		free(str_42);
	if (str42_2)
		free(str42_2);
	if (db_str_42)
		ft_free_double(&db_str_42);
	if (lst_42)
		ft_lstclear(&lst_42, &ft_destroy_dict_entry);
}

void	ft_lst_db_str_malloc(t_ctx *ctx, t_list *lst_42, char **db_str_42,
		char *str_42)
{
	if (str_42)
		free(str_42);
	if (db_str_42)
		ft_free_double(&db_str_42);
	if (lst_42)
		ft_lstclear(&lst_42, &ft_destroy_dict_entry);
	ft_error(ctx, MALLOC_ERROR, EXIT_FAILURE);
}

void	ft_free_and_error(char *to_free, t_ctx *ctx, char *msg, int code)
{
	free(to_free);
	ft_error(ctx, msg, code);
}

void	ft_free_db_and_error(char **to_free, t_ctx *ctx, char *msg, int code)
{
	ft_free_double(&to_free);
	ft_error(ctx, msg, code);
}
