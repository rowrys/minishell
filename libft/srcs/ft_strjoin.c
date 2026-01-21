/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 05:51:17 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_calloc(sizeof(char), size + 1);
	size = 0;
	while (ptr && s1 && *s1)
	{
		ptr[size] = *s1;
		size++;
		s1++;
	}
	while (ptr && s2 && *s2)
	{
		ptr[size] = *s2;
		size++;
		s2++;
	}
	return (ptr);
}
