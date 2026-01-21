/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:50:47 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;
	void			*result;
	size_t			i;

	str = (unsigned char *)s;
	c2 = (unsigned char)c;
	result = NULL;
	i = 0;
	if (!n)
		return (0);
	while (str[i] != c2 && i < (n - 1))
		i++;
	if (str[i] == c2)
		result = (void *)(str + i);
	return (result);
}
