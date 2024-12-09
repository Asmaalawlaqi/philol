/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llto2darr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:10:15 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:10:16 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_llto2darr(t_list *list, char *(*f)(void *))
{
	int		len;
	int		i;
	char	**arr;

	len = ft_lstsize(list);
	i = -1;
	arr = malloc((len + 1) * sizeof(char *));
	while (++i < len)
	{
		arr[i] = f(list->content);
		list = list->next;
	}
	arr[i] = NULL;
	return (arr);
}
