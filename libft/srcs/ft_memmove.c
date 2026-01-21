/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:13:17 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest < src && n)
	{
		while (i < n)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else if (dest > src && n)
	{
		while (n)
		{
			n--;
			((char *)dest)[n] = ((const char *)src)[n];
		}
	}
	return (dest);
}
