/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:10:20 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:10:21 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*list;

	if (!lst)
		return ;
	if (*lst != NULL)
	{
		list = ft_lstlast(*lst);
		list->next = new_node;
	}
	else
		*lst = new_node;
}
