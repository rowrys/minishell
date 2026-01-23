/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:07:23 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/23 16:16:57 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	ft_parse(t_ctx *ctx)
{
	ft_parse_line(ctx);
	ft_parse_cmd(ctx);
}
