/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:10:12 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:10:13 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	long	temp;

	len = n <= 0;
	temp = n;
	while (n && ++len)
		n /= 10;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (!temp)
		res[0] = 48;
	if (temp < 0)
	{
		res[0] = '-';
		temp *= -1;
	}
	while (len - 1 >= 0 && temp && len--)
	{
		res[len] = temp % 10 + 48;
		temp /= 10;
	}
	return (res);
}
