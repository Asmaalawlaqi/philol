/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:23:53 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:23:55 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_length_min(t_list **stackB)
{
	int		i;
	t_list	*node;

	node = *stackB;
	i = 0;
	while (node != NULL)
	{
		if (find_min(stackB) == node->content)
			break ;
		i++;
		node = node->next;
	}
	return (i);
}

int	find_length_index(t_list **stackA, int index)
{
	int		i;
	t_list	*node;

	i = 0;
	node = *stackA;
	while (node != NULL)
	{
		if (node->index == index)
			break ;
		i++;
		node = node->next;
	}
	return (i);
}

void	fill_index(t_list **stackA)
{
	t_list	*node;
	t_list	*temp_node;
	int		i;

	i = 1;
	temp_node = *stackA;
	node = *stackA;
	while (temp_node != NULL)
	{
		node = *stackA;
		while (node != NULL)
		{
			if (temp_node->content > node->content)
				i++;
			node = node->next;
		}
		temp_node->index = i;
		i = 1;
		temp_node = temp_node->next;
	}
}

int	sorted(t_list **stackA)
{
	t_list	*a;

	a = *stackA;
	while (a->next)
	{
		if (a->content > a->next->content)
			return (0);
		a = a->next;
	}
	return (1);
}
