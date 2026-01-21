/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:23:07 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(char *dst, size_t n)
{
	size_t	size;

	size = 0;
	while (dst && dst[size] && size < n)
		size++;
	return (size);
}
