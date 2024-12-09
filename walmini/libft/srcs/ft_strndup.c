/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:11:42 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:11:43 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*res;
	int		i;

	if (str == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (n + 1));
	i = -1;
	while (++i < n && str[i] != '\0')
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}
