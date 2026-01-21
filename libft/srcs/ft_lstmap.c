/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolin <mcolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:00:14 by ykolacze          #+#    #+#             */
/*   Updated: 2026/01/19 13:47:16 by mcolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*content;

	new = NULL;
	while (lst && f && del)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (temp)
		{
			ft_lstadd_back(&new, temp);
			lst = lst->next;
		}
		else
		{
			del(content);
			ft_lstclear(&new, del);
			return (NULL);
		}
	}
	return (new);
}
