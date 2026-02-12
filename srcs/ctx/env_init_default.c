/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_default.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:30:38 by ykolacze          #+#    #+#             */
/*   Updated: 2026/02/12 13:17:37 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

#define DEFAULT_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin\
:/usr/bin:/sbin:/bin"
#define DEFAULT_OLDPWD "OLDPWD"

static char	*ft_init_pwd(char **result)
{
	char	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	if (!pwd)
	{
		free(tmp);
		ft_free_db_and_error(result, NULL, MALLOC_ERROR, EXIT_FAILURE);
	}
	return (pwd);
}

char	**ft_env_default(void)
{
	char	**result;

	result = ft_calloc(4, sizeof(char *));
	if (!result)
		ft_error(NULL, MALLOC_ERROR, EXIT_FAILURE);
	result[0] = ft_init_pwd(result);
	result[1] = ft_strdup(DEFAULT_PATH);
	if (!result[1])
		ft_free_db_and_error(result, NULL, MALLOC_ERROR, EXIT_FAILURE);
	result[2] = ft_strdup(DEFAULT_OLDPWD);
	if (!result[2])
		ft_free_db_and_error(result, NULL, MALLOC_ERROR, EXIT_FAILURE);
	return (result);
}
