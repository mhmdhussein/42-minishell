/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:16:08 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/18 14:24:00 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*newcontent;
	t_list	*newlist;
	t_list	*current;
	t_list	*newnode;

	if (!lst || !f || !del)
		return (NULL);
	newlist = NULL;
	current = lst;
	newnode = NULL;
	while (current)
	{
		newcontent = f(current->content);
		if (!newcontent)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		newnode = ft_lstnew(newcontent);
		ft_lstadd_back(&newlist, newnode);
		current = current->next;
	}
	return (newlist);
}
