/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:58:15 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/27 19:36:30 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_dict_value(t_ctx *ctx, t_list *tmp_dict, char *name)
{
	char			*result;
	t_dict_entry	*entry;
	
	result = NULL;
	while (tmp_dict)
	{
		entry = tmp_dict->content;
		if (!ft_strcmp(entry->key, name))
		{
			result = ft_strdup(entry->value);
		///////////*REMOVE DOWN */
			#include <stdio.h>
			printf("%s\n", result);
	/////////REMOVE UPPPP/////////////
			// if (!result && tmp_entry->value)
			// {
ctx->last_error = ctx->last_error;
			// 	free(name);
			// 	ft_error();
			// }
			break ;
		}
		tmp_dict = tmp_dict->next;
	}
	return (result);
}