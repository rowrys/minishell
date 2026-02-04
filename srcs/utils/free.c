/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:20:35 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/04 10:26:39 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

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