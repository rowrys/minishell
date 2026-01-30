/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 09:52:28 by mcolin            #+#    #+#             */
/*   Updated: 2026/01/30 19:53:43 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdbool.h>

void	ft_close(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void	ft_replace_fd(int *old_fd, int new_fd)
{
	ft_close(old_fd);
	*old_fd = new_fd;
}

bool	ft_is_redir_key(t_key key)
{
	if (key == KEY_LREDIR
		|| key == KEY_RREDIR
		|| key == KEY_HERE_DOC
		|| key == KEY_APPEND)
		return (true);
	return (false);
}

int	ft_go_to(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_skip(char *str, char *charset)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && ft_strchr(charset, str[i]))
		i++;
	return (i);
}
