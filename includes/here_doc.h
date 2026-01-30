/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:16:41 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/30 14:19:46 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"
# include <stdbool.h>

/*here_doc*/
bool	ft_here_doc(t_ctx *ctx);

/*parse_limiter*/
char	*ft_get_limiter(t_ctx *ctx, char *block, bool *do_expand);
bool    ft_check_limiter(char *line, char *limiter, int *total_size_write);

#endif