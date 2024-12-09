/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:10:40 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:10:41 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;
	t_list	*head;

	if (!lst)
		return (NULL);
	head = ft_lstnew((*f)(lst->content));
	if (!head)
		return (NULL);
	(void)(*del);
	temp = head;
	temp2 = lst->next;
	while (temp2)
	{
		temp->next = ft_lstnew((*f)(temp2->content));
		temp = temp->next;
		if (!temp)
			return (NULL);
		temp2 = temp2->next;
	}
	return (head);
}
