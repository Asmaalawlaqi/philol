/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:22:47 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:29:37 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort2na(t_list **stackA)
{
	t_list	*node;
	int		n1;
	int		n2;

	node = *stackA;
	n1 = node->content;
	n2 = node->next->content;
	if (n1 > n2)
		sa(stackA);
}

void	sort3n(t_list **stackA)
{
	int	n1;
	int	n2;
	int	n3;

	n1 = (*stackA)->content;
	n2 = (*stackA)->next->content;
	n3 = (*stackA)->next->next->content;
	if ((n1 < n2) && (n2 < n3) && (n1 < n3))
		return ; //: Simple swap if needed.
	if ((n1 > n2) && (n2 < n3) && (n1 < n3))
		sa(stackA); //se specific conditions to swap and rotate elements into the correct order.
	else if ((n1 > n2) && (n2 > n3) && (n1 > n3))
	{
		sa(stackA);//Move the minimum element to stackB, sort the remaining 3 elements, and move the minimum element back.
		rra(stackA);
	}
	else if ((n1 < n2) && (n2 > n3) && (n1 > n3))
		rra(stackA);
	else if ((n1 < n2) && (n2 > n3) && (n1 < n3))
	{
		sa(stackA);
		ra(stackA);
	}
	else if ((n1 > n2) && (n2 < n3) && (n1 > n3))
		ra(stackA);
}

void	sort4n(t_list **stackA, t_list **stackB)
{
	int	min;

	min = find_min(stackA);
	while ((*stackA)->content != min)
	{
		ra(stackA);
	}
	pb(stackA, stackB);
	sort3n(stackA);
	pa(stackB, stackA);
}

void	sort5n(t_list **stackA, t_list **stackB)
{
	int	min;

	min = find_min(stackA);
	while ((*stackA)->content != min)
	{
		if (find_length_min(stackA) > ft_lstsize(*stackA) / 2)
			rra(stackA);
		else
			ra(stackA);
	}
	pb(stackA, stackB);
	sort4n(stackA, stackB);
	pa(stackB, stackA);
}


//2 elements: Simple swap if needed.
///3 elements: Use specific conditions to swap and rotate elements into the correct order.
//4 elements: Move the minimum element to stackB, sort the remaining 3 elements, and move the minimum element back.
//5 elements: Move the minimum element to stackB, sort the remaining 4 elements, and move the minimum element back.
//more than 5 ; Find the minimum element and move it to the top of the stack.
// Push the minimum element to stackB.
// Sort the remaining 4 elements in stackA using sort4n.
// Push the minimum element back into stackA after sorting.

