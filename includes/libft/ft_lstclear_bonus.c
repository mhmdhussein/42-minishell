/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohhusse <mohhusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:04:10 by mohhusse          #+#    #+#             */
/*   Updated: 2024/06/18 14:23:27 by mohhusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next;	

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (del)
			del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
