/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 06:19:04 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (c == s1[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	start;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isset(set, s1[start]))
		start++;
	size = ft_strlen(s1) - 1;
	while (s1[size] && ft_isset(set, s1[size]))
		size--;
	size += (1 - start);
	ptr = ft_substr(s1, start, size);
	return (ptr);
}
