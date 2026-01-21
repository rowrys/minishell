/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:07:51 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if ((!s1 && !s2) || !n)
		return (0);
	if (!s1 && s2)
		return (-1);
	if (s1 && !s2)
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1 && str1[i] && str1[i] == str2[i] && i < (n - 1))
		i++;
	return (str1[i] - str2[i]);
}
