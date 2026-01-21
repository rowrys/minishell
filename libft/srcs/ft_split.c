/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:06:07 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_array(char const *s, char c)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			counter++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	size;
	size_t	nb_array;

	nb_array = ft_count_array(s, c);
	ptr = ft_calloc(sizeof(char **), (nb_array + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < nb_array)
	{
		while (*s && *s == c)
			s++;
		size = 0;
		while (*(s + size) && *(s + size) != c)
			size++;
		ptr[i] = ft_substr(s, 0, size);
		if (!ptr[i])
			ft_free_double(&ptr);
		if (!ptr || !ptr[i])
			return (NULL);
		s += size;
	}
	return (ptr);
}
