/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:23:13 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	size_l;

	size_l = ft_strlen(little);
	if (!size_l)
		return ((char *)big);
	while (*big && len)
	{
		if (*big == *little && size_l <= len)
		{
			if (!ft_strncmp(big, little, size_l))
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (0);
}
