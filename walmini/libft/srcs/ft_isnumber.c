/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:10:09 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:10:10 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *num)
{
	int	i;

	i = 0;
	if (ft_isdigit(num[0]) == 0 && (num[0] != '-' && num[0] != '+'))
		return (0);
	while (num[++i] != 0)
	{
		if (ft_isdigit(num[i]) == 0)
			return (0);
	}
	return (1);
}
