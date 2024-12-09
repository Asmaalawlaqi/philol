/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmalawl <asmalawl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:30:07 by asmalawl          #+#    #+#             */
/*   Updated: 2024/05/26 14:30:08 by asmalawl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	tl;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		tl = len1 + len2;
		res = (char *)malloc(sizeof(char) * (tl + 1));
		if (res == NULL)
		{
			return (NULL);
		}
		ft_strlcpy(res, s1, tl + 1);
		ft_strlcat(res, s2, tl + 1);
		return (res);
	}
	return (NULL);
}
