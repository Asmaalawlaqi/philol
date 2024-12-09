/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:11:39 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:11:40 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	cmp;

	i = 0;
	cmp = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (!cmp && i < n && s1[i] && s2[i])
	{
		cmp = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if (!cmp && i < n && (s1[i] || s2[i]))
		cmp = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (cmp);
}
