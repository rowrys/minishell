/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:16:55 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(unsigned int n)
{
	int	power;

	power = 1;
	while (n)
	{
		power++;
		n /= 10;
	}
	return (power);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				size;
	unsigned int	n2;

	n2 = n;
	if (n < 0)
		n2 = -n;
	size = ft_power(n2);
	if (n > 0)
		size--;
	ptr = ft_calloc(sizeof(char), (size + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
		ptr[0] = '-';
	if (n == 0)
		ptr[0] = '0';
	while (n2)
	{
		ptr[size - 1] = '0' + (char)(n2 % 10);
		n2 /= 10;
		size--;
	}
	return (ptr);
}
