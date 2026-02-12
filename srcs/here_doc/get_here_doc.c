/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 08:58:27 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/12 13:33:57 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "parse.h"

#include <signal.h>
#include <stdbool.h>
#include <readline/readline.h>

extern int	g_was_killed;

static void	ft_expand_and_write(t_ctx *ctx, char *line, int fd, bool do_expand)
{
	if (do_expand)
		line = ft_manage_expand(ctx, line, 0);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

bool	ft_get_here_doc(t_ctx *ctx, char *limiter, bool do_expand, int fd)
{
	char	*line;
	int		total_size_write;
	int		tmp_stdin;

	total_size_write = 0;
	tmp_stdin = dup(STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (g_was_killed == SIGINT)
		{
			g_was_killed = 0;
			dup2(tmp_stdin, STDIN_FILENO);
			close(tmp_stdin);
			return (true);
		}
		if (ft_check_limiter(line, limiter, &total_size_write))
		{
			close(tmp_stdin);
			return (false);
		}
		ft_expand_and_write(ctx, line, fd, do_expand);
	}
	close(tmp_stdin);
	return (false);
}
