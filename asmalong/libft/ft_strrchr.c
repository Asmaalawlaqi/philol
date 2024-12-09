/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:20:09 by asmalawl          #+#    #+#             */
/*   Updated: 2024/04/29 10:42:30 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = (char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == ch)
			return ((char *)(&s[i]));
		i--;
	}
	return (NULL);
}
