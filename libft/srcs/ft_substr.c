/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 04:08:18 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		size = 0;
	else
		size = ft_strnlen((char *)(s + start), len);
	ptr = ft_calloc(sizeof(char), size + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s[start + i];
		i++;
	}
	return (ptr);
}
