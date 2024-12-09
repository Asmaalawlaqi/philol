/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:23:13 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:23:18 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_list **stackB)
{
	int	a;
	int	b;

	if (*stackB == NULL || ft_lstsize(*stackB) == 1)
		return ;
	a = (*stackB)->content;
	b = (*stackB)->next->content;
	(*stackB)->next->content = a;
	(*stackB)->content = b;
	ft_putstr_fd("sb\n", 1);
}

void	pa(t_list **stackB, t_list **stackA)
{
	t_list	*temp;
	t_list	*top;

	top = *stackB;
	temp = NULL;
	if (*stackB)
		temp = (*stackB)->next;
	if (*stackB == NULL)
		return ;
	ft_lstadd_front(stackA, top);
	*stackB = temp;
	ft_putstr_fd("pa\n", 1);
}

void	rb(t_list **stackB)
{
	t_list	*top;
	t_list	*last;

	if (*stackB == NULL || ft_lstsize(*stackB) == 1)
		return ;
	top = *stackB;
	last = ft_lstlast(*stackB);
	*stackB = top->next;
	last->next = top;
	top->next = NULL;
	ft_putstr_fd("rb\n", 1);
}

void	rrb(t_list **stackB)
{
	t_list	*first;
	t_list	*secend_last;
	t_list	*last;

	last = ft_lstlast(*stackB);
	secend_last = *stackB;
	first = *stackB;
	if (*stackB == NULL || ft_lstsize(*stackB) == 1)
		return ;
	while (secend_last->next->next != NULL)
		secend_last = secend_last->next;
	secend_last->next = NULL;
	last->next = first;
	*stackB = last;
	ft_putstr_fd("rrb\n", 1);
}
