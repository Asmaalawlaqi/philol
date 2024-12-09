/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_a.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:23:22 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:23:25 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **stackA)
{
	int	a;
	int	b;

	if (*stackA == NULL || ft_lstsize(*stackA) == 1)
		return ;
	a = (*stackA)->content;
	b = (*stackA)->next->content;
	(*stackA)->next->content = a;
	(*stackA)->content = b;
	ft_putstr_fd("sa\n", 1);
}

void	pb(t_list **stackA, t_list **stackB)
{
	t_list	*top;
	t_list	*temp;

	temp = (*stackA)->next;
	top = *stackA;
	if (*stackA == NULL)
		return ;
	ft_lstadd_front(stackB, top);
	*stackA = temp;
	ft_putstr_fd("pb\n", 1);
}

void	ra(t_list **stackA)
{
	t_list	*top;
	t_list	*last;

	if (*stackA == NULL || ft_lstsize(*stackA) == 1)
		return ;
	top = *stackA;
	last = ft_lstlast(*stackA);
	*stackA = top->next;
	last->next = top;
	top->next = NULL;
	ft_putstr_fd("ra\n", 1);
}

void	rra(t_list **stackA)
{
	t_list	*first;
	t_list	*secend_last;
	t_list	*last;

	last = ft_lstlast(*stackA);
	secend_last = *stackA;
	first = *stackA;
	if (*stackA == NULL || ft_lstsize(*stackA) == 1)
		return ;
	while (secend_last->next->next != NULL)
		secend_last = secend_last->next;
	secend_last->next = NULL;
	last->next = first;
	*stackA = last;
	ft_putstr_fd("rra\n", 1);
}
