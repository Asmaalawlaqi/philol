/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:27:48 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:27:49 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int enc, size_t num)
{
	size_t	i;
	char	*p;

	p = (char *)str;
	i = 0;
	while (i < num)
	{
		p[i] = enc;
		i++;
	}
	return (str);
}
